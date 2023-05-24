#define CONSOLE_LOGGING_ALL
#define CONSOLE_LOGGING_NOTIFIES
#define CONSOLE_LOGGING_WARNINGS
#define CONSOLE_LOGGING_ERRORS

using ConsoleSugar;
using NetworkPackets;
using NetworkPackets.Packets;
using NetworkPackets.Packets.Download;
using NetworkPackets.Packets.Echo;
using NetworkPackets.Packets.Files;
using NetworkPackets.Packets.Time;
using Shared;
using SyncShared;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Reflection.Metadata;
using System.Reflection.Metadata.Ecma335;

namespace SynchronousServer
{
    internal class SyncUdpServer : IDisposable
    {
        public const int BufferSize = 65507;

        private readonly Socket _mainSocket;
        private readonly int _port;
        private byte[] _buffer;
        private readonly DefaultPacketsResolver _resolver = new();

        private readonly FileManager _fileManager;

        private bool _disposedValue;

        private readonly List<Connection> _connections = new();
        private Connection _currentConnection;
        Dictionary<Connection, PacketBase> _requestsQeue = new();

        public SyncUdpServer(int mainPort, string fileHoldersPathes)
        {
            _mainSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            _port = mainPort;
            _mainSocket.Bind(new IPEndPoint(IPAddress.Any, _port));
            _port = mainPort;
            _buffer = new byte[BufferSize];
            _fileManager = new FileManager(fileHoldersPathes);
            FileChunker.FileChunkSize = BufferSize - 60;
        }

        public void Start()
        {
#if CONSOLE_LOGGING_NOTIFIES || CONSOLE_LOGGING_ALL
            ConsoleHelpers.LogNotify($"Server Started on ep: {_mainSocket.LocalEndPoint}", typeof(SyncUdpServer).ToString(), true);
#endif

            while (true)
            {
#if CONSOLE_LOGGING_ALL
                ConsoleHelpers.Log($"Waiting for new connection...", typeof(SyncUdpServer).ToString(), true);
#endif
                //if (TempFile.IsExist())
                //{
                //    RestoreUpload();
                //}
                //else
                //{
                //    SyncNetworkingHelpers.SendPacket(_mainSocket, new UploadFileMessage(), _endPointClient);
                //}

                HandleConnectedSocket(_mainSocket);
            }
        }

        private void HandleConnectedSocket(Socket handler)
        {
            EndPoint endPointClient = new IPEndPoint(IPAddress.Any, 0);
            List<Connection> toRemove = new();
            while (true)
            {
                try
                {
                    PacketBase decodedPacked;
                    if (!_requestsQeue.Any())
                    {
                        decodedPacked = SyncNetworkingHelpers.ReceivePacket(handler, ref _buffer, _resolver, ref endPointClient);
                    }
                    else
                    {
                        var connection = _requestsQeue.First().Key;
                        decodedPacked = _requestsQeue.First().Value;
                        endPointClient = connection.EndPoint;
                        _requestsQeue.Remove(connection);
                    }

                    if ((_currentConnection = _connections.Find(x => x.EndPoint == endPointClient)) == null)
                    {
                        _connections.Add(new Connection(_mainSocket, endPointClient));
#if CONSOLE_LOGGING_NOTIFIES || CONSOLE_LOGGING_ALL
                        ConsoleHelpers.LogNotify($"New connection: {endPointClient}", typeof(SyncUdpServer).ToString(), true);
#endif
                        _currentConnection = _connections.Last();
                    }

                    if (!HandlePacket(decodedPacked))
                        _connections.Remove(_currentConnection);
                    //task delay?
                }
                catch (SocketException ex)
                {
#if CONSOLE_LOGGING_ERRORS || CONSOLE_LOGGING_ALL
                    ConsoleHelpers.LogError($"Error in handling socket: {ex.Message}", typeof(SyncUdpServer).ToString(), true);
#endif
                    _connections.Remove(_currentConnection);

                    break;
                }
            }
        }

        private bool HandlePacket(PacketBase decodedPacket)
        {
#if CONSOLE_LOGGING_NOTIFIES || CONSOLE_LOGGING_ALL
            ConsoleHelpers.LogNotify($"Received packet: {decodedPacket.GetType().Name} (ID {decodedPacket.PacketID} NUM {decodedPacket.CurrentPacketNumber})", typeof(SyncUdpServer).ToString(), true);
#endif
            PacketBase? responsePacket = null;

            switch (decodedPacket)
            {
                case ExitMessage:
                    return false;
                case StartMessage:
                    return true;
                case EchoRequest echoRequest:
                    responsePacket = HandleEchoRequest(echoRequest);
                    break;
                case TimeRequest timeRequest:
                    responsePacket = HandleTimeRequest(timeRequest);
                    break;
                case StartFileDownloadRequest sfdRequest:
                    responsePacket = HandleStartFileDownloadRequest(sfdRequest);
                    break;
                case DownloadFileRequest dfRequest:
                    responsePacket = HandleDownloadFileRequest(dfRequest);
                    break;
                case GetDownloadableFilesListRequest getDownloadableFilesListRequest:
                    responsePacket = HandleGetDownloadableFilesListRequest(getDownloadableFilesListRequest);
                    break;
                case UploadFileMessage uploadMessage:
                    HandleUpload(uploadMessage);
                    break;
                case FileWindowStart fwStart:
                    HandleFileWindow(fwStart);
                    break;
                default:
                    break;
            }

            if (responsePacket != null)
            {
                SyncNetworkingHelpers.SendPacket(_currentConnection.Socket, responsePacket, _currentConnection.EndPoint);
            }
            return true;
        }


        //        private void RestoreUpload()
        //        {
        //            TempFile.GetInfo(out var allChunks, out var downloadedChunks, out var fileKey, out EndPoint endPoint);
        //            _endPointClient = endPoint;
        //#if CONSOLE_LOGGING_NOTIFIES || CONSOLE_LOGGING_ALL
        //            ConsoleHelpers.LogNotify($"New connection: {_endPointClient}", typeof(SyncUdpServer).ToString(), true);
        //            ConsoleHelpers.LogWarning("Some file is not loaded! Trying to restore download!", typeof(SyncUdpServer).ToString(), true);
        //#endif
        //            SyncNetworkingHelpers.SendPacket(_mainSocket, new UploadFileMessage(System.Text.Encoding.UTF8.GetString(fileKey)), _endPointClient);

        //            for (long i = downloadedChunks; i < allChunks; i++)
        //            {
        //                var fileRequest = new DownloadFileRequest();
        //                fileRequest.NeededChunk = i;
        //                fileRequest.FileKey = fileKey;
        //                var fileResponse = RequestClient<DownloadFileResponse>(fileRequest);
        //                if (fileResponse != null)
        //                    TempFile.Add(i + 1, fileResponse!.Data!);
        //                else
        //                    i--;
        //            }

        //            SyncNetworkingHelpers.SendPacket(_mainSocket, new UploadFileMessage(), _endPointClient);

        //            string path = System.Text.Encoding.UTF8.GetString(fileKey);
        //            path = Path.Combine(Directory.GetCurrentDirectory(), "Files", path);
        //            TempFile.Finish(path);

        //            if (OperatingSystem.IsWindows())
        //            {
        //                string cmd = "explorer.exe";
        //                string arg = "/select, " + path;
        //                Process.Start(cmd, arg);
        //            }
        //        }

        private void HandleFileWindow(FileWindowStart fwStart)
        {
            for (int i = fwStart.StartChunk; i < fwStart.StartChunk + fwStart.ChunkCount; i++)
            {
                string filename = System.Text.Encoding.UTF8.GetString(fwStart!.FileKey!);
                if (_fileManager.TryGetFile(filename, out FileInfo? finfo))
                {
#if CONSOLE_LOGGING_ALL
                    ConsoleHelpers.LogNotify($"requested file name: {filename} Chunk: {i}");
#endif
                    var dfResponse = new DownloadFileResponse();
                    dfResponse.Data = FileChunker.GetChunk(finfo!, i);
                    SyncNetworkingHelpers.SendPacket(_currentConnection.Socket, dfResponse, _currentConnection.EndPoint);
                }
            }
            SyncNetworkingHelpers.SendPacket(_currentConnection.Socket, new FileWindowEnd(), _currentConnection.EndPoint);
        }

        private void HandleUpload(UploadFileMessage uploadMessage)
        {
            var startRequest = new StartFileDownloadRequest();
            string? fileName = uploadMessage.FileName;
            startRequest.FileName = fileName;

            var startResponse = RequestClient<StartFileDownloadResponse>(startRequest);

            if (startResponse == null)
                throw new NullReferenceException(nameof(startResponse));


            if (File.Exists(Path.Combine(Directory.GetCurrentDirectory(), "Files", fileName!)))
                File.Delete(Path.Combine(Directory.GetCurrentDirectory(), "Files", fileName!));

            if (TempFile.IsExist())
                TempFile.Delete();
            TempFile.Create(startResponse.Chunks, 0, startResponse.FileKey!, _currentConnection.EndPoint.ToString()!);

            Stopwatch sw = Stopwatch.StartNew();
            int recievedBytes = 0;
            if (startResponse.Chunks > 0)
            {
                for (int i = 0; i < startResponse.Chunks; i++)
                {
                    var fileRequest = new DownloadFileRequest();
                    fileRequest.NeededChunk = i;
                    fileRequest.FileKey = startResponse.FileKey;
                    var fileResponse = RequestClient<DownloadFileResponse>(fileRequest);
                    recievedBytes += fileResponse!.Data!.Length;
                    TempFile.Add(i + 1, fileResponse!.Data!);
                }
            }
            else
            {
                ConsoleHelpers.LogError(System.Text.Encoding.UTF8.GetString(startResponse!.FileKey!));
                SyncNetworkingHelpers.SendPacket(_currentConnection.Socket, new UploadFileMessage(), _currentConnection.EndPoint);
                return;
            }
            sw.Stop();

            SyncNetworkingHelpers.SendPacket(_currentConnection.Socket, new UploadFileMessage(), _currentConnection.EndPoint);

            ConsoleHelpers.LogNotify($"Bitrate is {(float)recievedBytes / (float)sw.ElapsedMilliseconds / 1000f} MB/s");

            string path = System.Text.Encoding.UTF8.GetString(startResponse!.FileKey!);
            path = Path.Combine(Directory.GetCurrentDirectory(), "Files", path);
            TempFile.Finish(path);

            if (OperatingSystem.IsWindows())
            {
                string cmd = "explorer.exe";
                string arg = "/select, " + path;
                Process.Start(cmd, arg);
            }
        }

        private PacketBase HandleGetDownloadableFilesListRequest(GetDownloadableFilesListRequest getDownloadableFilesListRequest)
        {
            var response = new ViewServerFilesResponse();
            var c = _fileManager.GetFiles().Length;
            var arr = new string[c];

            int i = -1;

            foreach (var f in _fileManager.GetFiles())
            {
                arr[++i] = f;
            }

            response.FilesNames = arr;
            return response;
        }

        //        private PacketBase? HandleDownloadFileAuthorizedRequest(Socket handler, DownloadFileAuthorizedRequest dlfaRequest)
        //        {
        //            var response = new DownloadFileAuthorizedResponse();

        //            if (dlfaRequest.Key == null)
        //            {
        //                response.Result = false;
        //                response.FailReason = DownloadFileAuthorizedResponse.FailReasons.WrongKey;
        //                return response;
        //            }

        //            //var fileName = "ranggyu.mp4";
        //            var fileName = System.Text.Encoding.UTF8.GetString(dlfaRequest.Key);

        //#if CONSOLE_LOGGING_ALL
        //            ConsoleHelpers.LogNotify($"requested file name: {fileName}");
        //#endif

        //            if (!_fileManager.TryGetFile(fileName, out var finfo))
        //            {
        //                response.Result = false;
        //                response.FailReason = DownloadFileAuthorizedResponse.FailReasons.Other;
        //                return response;
        //            }

        //            response.Result = true;
        //            response.FileSize = finfo!.Length;

        //            SyncNetworkingHelpers.SendPacket(handler, response);

        //            var fsOptions = new FileStreamOptions()
        //            {
        //                Access = FileAccess.Read,
        //                Mode = FileMode.Open,
        //                Share = FileShare.Read,
        //            };

        //            var fstream = finfo.Open(fsOptions);

        //            var h = new SyncStreamSenderHelper(fstream, handler);
        //            h.SendAll();

        //            return null;
        //        }

        private PacketBase HandleStartFileDownloadRequest(StartFileDownloadRequest request)
        {
            var response = new StartFileDownloadResponse();
            if (_fileManager.TryGetFile(request!.FileName!, out var finfo))
            {
                response.Chunks = FileChunker.GetFileChunksCount(finfo);
                response.FileKey = System.Text.Encoding.UTF8.GetBytes(request!.FileName!);
            }
            else
            {
                response.Chunks = 0;
                response.FileKey = System.Text.Encoding.UTF8.GetBytes("File does not exist on server");
            }
            return response;
        }

        private PacketBase HandleDownloadFileRequest(DownloadFileRequest request)
        {
            var response = new DownloadFileResponse();
            string filename = System.Text.Encoding.UTF8.GetString(request!.FileKey!);
            if (_fileManager.TryGetFile(filename, out FileInfo? finfo))
            {
#if CONSOLE_LOGGING_ALL
                ConsoleHelpers.LogNotify($"requested file name: {filename} Chunk: {request.NeededChunk}");
#endif
                response.Data = FileChunker.GetChunk(finfo!, request.NeededChunk);
            }
            return response;
        }

        private static PacketBase HandleEchoRequest(EchoRequest echoRequest)
        {
            PacketBase? responsePacket;
            EchoResponse response = new();
            response.EchoMessage = echoRequest.Message;
            responsePacket = response;
            return responsePacket;
        }

        private PacketBase? HandleTimeRequest(TimeRequest timeRequest)
        {
            TimeResponse response = new();
            response.TimeMessage = DateTime.Now.ToString("T");
            return response;
        }

        private T? RequestClient<T>(PacketBase request) where T : PacketBase
        {
            SyncNetworkingHelpers.SendPacket(_currentConnection.Socket, request, _currentConnection.EndPoint);
            EndPoint endPoint = new IPEndPoint(IPAddress.Any, 0);
            PacketBase raw;
            while (true)
            {
                raw = SyncNetworkingHelpers.ReceivePacket(_currentConnection.Socket, ref _buffer, _resolver, ref endPoint);
                if (endPoint == _currentConnection.EndPoint)
                    break;
                else
                    _requestsQeue.Add(new Connection(_mainSocket, endPoint), raw);
            }

            return raw as T;
        }

        #region IDisposable
        protected virtual void Dispose(bool disposing)
        {
            if (!_disposedValue)
            {
                if (disposing)
                {
                    // TODO: освободить управляемое состояние (управляемые объекты)
                    _mainSocket.Dispose();
                }

                // TODO: освободить неуправляемые ресурсы (неуправляемые объекты) и переопределить метод завершения
                // TODO: установить значение NULL для больших полей
                _disposedValue = true;
            }
        }

        // // TODO: переопределить метод завершения, только если "Dispose(bool disposing)" содержит код для освобождения неуправляемых ресурсов
        // ~TcpServer()
        // {
        //     // Не изменяйте этот код. Разместите код очистки в методе "Dispose(bool disposing)".
        //     Dispose(disposing: false);
        // }

        public void Dispose()
        {
            // Не изменяйте этот код. Разместите код очистки в методе "Dispose(bool disposing)".
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }
        #endregion
    }
}