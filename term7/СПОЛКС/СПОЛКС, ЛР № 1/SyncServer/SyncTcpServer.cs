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

namespace SynchronousServer
{
    internal class SyncTcpServer : IDisposable
    {
        public const int BufferSize = ushort.MaxValue;

        private readonly Socket _mainSocket;
        private Socket _handler;
        private readonly int _port;
        private readonly byte[] _buffer;
        private readonly DefaultPacketsResolver _resolver = new();

        private readonly FileManager _fileManager;

        private bool _disposedValue;

        public SyncTcpServer(int mainPort, string fileHoldersPathes, float timeoutSeconds = 10)
        {
            _mainSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            _mainSocket.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.TcpKeepAliveInterval, 1);
            _mainSocket.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.TcpKeepAliveRetryCount, 20);
            _mainSocket.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.TcpKeepAliveTime, 5);
            _mainSocket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.KeepAlive, true);

            _port = mainPort;
            _buffer = new byte[BufferSize];
            _fileManager = new FileManager(fileHoldersPathes);
        }

        public void Start()
        {
            InitAcceptingSocket();

#if CONSOLE_LOGGING_NOTIFIES || CONSOLE_LOGGING_ALL
            ConsoleHelpers.LogNotify($"Server Started on ep: {_mainSocket.LocalEndPoint}", typeof(SyncTcpServer).ToString(), true);
#endif

            while (true)
            {
#if CONSOLE_LOGGING_ALL
                ConsoleHelpers.Log($"Waiting for new connection...", typeof(SyncTcpServer).ToString(), true);
#endif
                var handler = _handler = _mainSocket.Accept();

#if CONSOLE_LOGGING_NOTIFIES || CONSOLE_LOGGING_ALL
                ConsoleHelpers.LogNotify($"New connection: {handler.RemoteEndPoint}", typeof(SyncTcpServer).ToString(), true);
#endif
                if (TempFile.IsExist())
                {
                    RestoreUpload();
                }
                else
                {
                    SyncNetworkingHelpers.SendPacket(handler, new UploadFileMessage());
                }

                HandleConnectedSocket(handler);
            }
        }

        private void HandleConnectedSocket(Socket handler)
        {
            while (true)
            {
                try
                {
                    var decodedPacked = SyncNetworkingHelpers.ReceivePacket(handler, _buffer, _resolver);
                    if (!HandlePacket(handler, decodedPacked))
                        return;
                    //task delay?
                }
                catch (SocketException ex)
                {
#if CONSOLE_LOGGING_ERRORS || CONSOLE_LOGGING_ALL
                    ConsoleHelpers.LogError($"error in handling socket: {ex.Message}", typeof(SyncTcpServer).ToString(), true);
#endif
                    if (handler != null)
                    {
                        handler.Dispose();
                    }

                    break;
                }
            }
        }

        private bool HandlePacket(Socket handler, PacketBase decodedPacket)
        {
#if CONSOLE_LOGGING_NOTIFIES || CONSOLE_LOGGING_ALL
            ConsoleHelpers.LogNotify($"received packet: {decodedPacket.GetType().Name} (ID {decodedPacket.PacketID})", typeof(SyncTcpServer).ToString(), true);
#endif
            PacketBase? responsePacket = null;

            switch (decodedPacket)
            {
                case ExitMessage:
                    return false;
                    break;
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
                default:
                    break;
            }

            if (responsePacket != null)
            {
                SyncNetworkingHelpers.SendPacket(handler, responsePacket);
            }
            return true;
        }

        private void RestoreUpload()
        {
            TempFile.GetInfo(out var allChunks, out var downloadedChunks, out var fileKey);

            SyncNetworkingHelpers.SendPacket(_handler, new UploadFileMessage(System.Text.Encoding.UTF8.GetString(fileKey)));

            for (long i = downloadedChunks; i < allChunks; i++)
            {
                var fileRequest = new DownloadFileRequest();
                fileRequest.NeededChunk = i;
                fileRequest.FileKey = fileKey;
                var fileResponse = RequestClient<DownloadFileResponse>(fileRequest);
                TempFile.Add(i + 1, fileResponse!.Data!);
            }

            SyncNetworkingHelpers.SendPacket(_handler, new UploadFileMessage());

            string path = System.Text.Encoding.UTF8.GetString(fileKey);
            path = Path.Combine(Directory.GetCurrentDirectory(), "Files", path);
            TempFile.Finish(path);

            if (OperatingSystem.IsWindows())
            {
                string cmd = "explorer.exe";
                string arg = "/select, " + path;
                Process.Start(cmd, arg);
            }
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
            TempFile.Create(startResponse.Chunks, 0, startResponse.FileKey!);

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
                SyncNetworkingHelpers.SendPacket(_handler, new UploadFileMessage());
                return;
            }
            sw.Stop();

            SyncNetworkingHelpers.SendPacket(_handler, new UploadFileMessage());

            ConsoleHelpers.LogNotify($"Bitrate is {recievedBytes / sw.ElapsedMilliseconds * 1000}");

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

        private void InitAcceptingSocket()
        {
            BindAcceptingSocket();
            _mainSocket.Listen(1);
        }

        private void BindAcceptingSocket()
        {
            if (_mainSocket.IsBound)
            {
                throw new Exception("socket already bound");
            }

            _mainSocket.Bind(new IPEndPoint(IPAddress.Any, _port));


        }

        private T? RequestClient<T>(PacketBase request) where T : PacketBase
        {
            SyncNetworkingHelpers.SendPacket(_handler, request);
            var raw = SyncNetworkingHelpers.ReceivePacket(_handler, _buffer, _resolver);

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