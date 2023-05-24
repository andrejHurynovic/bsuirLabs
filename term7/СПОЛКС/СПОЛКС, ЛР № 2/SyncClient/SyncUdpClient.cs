#define CONSOLE_LOGGING_ALL
//#define CONSOLE_LOGGING_NOTIFIES
//#define CONSOLE_LOGGING_WARNINGS
//#define CONSOLE_LOGGING_ERRORS

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

namespace SynchronousClient
{
    internal class SyncUdpClient : IDisposable
    {
        public const int BufferSize = 65507;

        private readonly Socket _mainSocket;
        private EndPoint _endPointServer;
        private byte[] _buffer;
        private readonly DefaultPacketsResolver _resolver = new();

        private bool _disposedValue;

        private FileManager _fileManager;

        public SyncUdpClient(EndPoint endPoint, int localPort)
        {
            _mainSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            _mainSocket.Bind(new IPEndPoint(IPAddress.Any, localPort));
            _endPointServer = endPoint;
            _buffer = new byte[BufferSize];

            _fileManager = new(Path.Combine(Directory.GetCurrentDirectory(), "Files"));
            FileChunker.FileChunkSize = BufferSize - 60;
        }


        public void Start()
        {
            SyncNetworkingHelpers.SendPacket(_mainSocket, new ExitMessage(), _endPointServer);
            SyncNetworkingHelpers.SendPacket(_mainSocket, new StartMessage(), _endPointServer);
            PacketBase? packet = SyncNetworkingHelpers.ReceivePacket(_mainSocket, ref _buffer, _resolver, ref _endPointServer);

            if (packet is UploadFileMessage message)
            {
                if (message.FileName != string.Empty)
                {
                    Upload(message.FileName, false);
                }
            }

            if (TempFile.IsExist())
            {
                RestoringDownload();
            }

            EnterCommandMode();
        }

        private void RestoringDownload()
        {
            ConsoleHelpers.LogWarning("Some file is not loaded! Trying to restore download!", typeof(SyncUdpClient).ToString(), true);

            TempFile.GetInfo(out var allChunks, out var dowloadedChunks, out var fileKey, out EndPoint endPoint);
            _endPointServer = endPoint;

            for (long i = dowloadedChunks; i < allChunks; i++)
            {
                var fileRequest = new DownloadFileRequest();
                fileRequest.NeededChunk = i;
                fileRequest.FileKey = fileKey;
                var fileResponse = RequestServer<DownloadFileResponse>(fileRequest);
                if (fileResponse == null || fileResponse.Data == null)
                    continue;
                TempFile.Add(i + 1, fileResponse!.Data!);
            }

            string path = System.Text.Encoding.UTF8.GetString(fileKey);
            path = Path.Combine(Directory.GetCurrentDirectory(), "Files", path);
            TempFile.Finish(path);
            Console.WriteLine($"File will saved to {path}");

            if (OperatingSystem.IsWindows())
            {
                ConsoleHelpers.LogSuccess("File downloaded! Open? (y/n)", typeof(SyncUdpClient).ToString(), true);

                if (Console.ReadLine() == "y")
                {
                    string cmd = "explorer.exe";
                    string arg = "/select, " + path;
                    Process.Start(cmd, arg);
                }
            }
        }

        private void EnterCommandMode()
        {
            while (true)
            {
                Console.WriteLine("Enter command:");
                var cmd = Console.ReadLine()?.ToLower();

                if (string.IsNullOrEmpty(cmd))
                    continue;

                if (!HandleCmd(ref cmd))
                    break;
            }
        }

        private bool HandleCmd(ref string cmd)
        {
            const string exitCmd = "exit";
            const string echoCmd = "echo";
            const string timeCmd = "time";
            const string downloadCmd = "download";
            const string getFilesCmd = "getfiles";
            const string uploadCmd = "upload";

            switch (cmd)
            {
                case exitCmd:
                    SendMessage(new ExitMessage());
                    Process.GetCurrentProcess().Kill();
                    break;
                case echoCmd:
                    CreateEchoRequest();
                    break;
                case timeCmd:
                    CreateTimeRequest();
                    break;
                case downloadCmd:
                    CreateDownloadRequest();
                    break;
                case getFilesCmd:
                    CreateGetFileNamesRequest();
                    break;
                case uploadCmd:
                    UploadFile();
                    break;
                default:
                    break;
            }

            return true;
        }

        private void UploadFile()
        {
            var c = _fileManager.GetFiles().Length;
            var arr = new string[c];

            int i = -1;

            Console.WriteLine("List of files :");
            foreach (var f in _fileManager.GetFiles())
            {
                arr[++i] = f;
                var n = arr[i];
                Console.WriteLine($"{i + 1}. {n}");
            }

            Console.WriteLine($"Upload? (1 - {c} / no)");

            if (int.TryParse(Console.ReadLine(), out var v))
            {
                if (v > 0 && v <= c)
                    Upload(arr[v - 1]);
            }
        }

        private void Upload(string? fileName, bool newUpload = true)
        {
            if (newUpload)
            {
                SendMessage(new UploadFileMessage(fileName!));
            }

            while (true)
            {
                var decodedPacket = SyncNetworkingHelpers.ReceivePacket(_mainSocket, ref _buffer, _resolver, ref _endPointServer);
                PacketBase? responsePacket = null;

                switch (decodedPacket)
                {
                    case UploadFileMessage:
                        return;
                    case StartFileDownloadRequest startRequest:
                        responsePacket = HandleStartFileDownloadRequest(startRequest);
                        break;
                    case DownloadFileRequest downloadRequest:
                        responsePacket = HandleDownloadFileRequest(downloadRequest);
                        break;
                    default:
                        break;
                }

                if (responsePacket != null)
                {
                    SyncNetworkingHelpers.SendPacket(_mainSocket, responsePacket, _endPointServer);
                }
            }
        }

        private PacketBase HandleDownloadFileRequest(DownloadFileRequest request)
        {
            var response = new DownloadFileResponse();
            string filename = System.Text.Encoding.UTF8.GetString(request!.FileKey!);
            if (_fileManager.TryGetFile(filename, out FileInfo? finfo))
            {
                response.Data = FileChunker.GetChunk(finfo!, request.NeededChunk);
            }
            return response;
        }

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

        private void CreateGetFileNamesRequest()
        {
            var gfRequest = new GetDownloadableFilesListRequest();
            var gfResponse = RequestServer<ViewServerFilesResponse>(gfRequest);

            if (gfResponse == null)
                throw new NullReferenceException(nameof(gfResponse));

            var arr = gfResponse.FilesNames!;
            var c = arr.Length;
            Console.WriteLine("List of files :");

            for (int i = -1; ++i < c;)
            {
                var n = arr[i];
                Console.WriteLine($"{i + 1}. {n}");
            }

            Console.WriteLine($"Download? (1 - {c} / no)");

            if (int.TryParse(Console.ReadLine(), out var v))
            {
                if (v > 0 && v <= c)
                    RequestDownload(arr[v - 1]);
            }
        }

        private void RequestDownload(string fileName)
        {
            var startRequest = new StartFileDownloadRequest();
            startRequest.FileName = fileName;

            var startResponse = RequestServer<StartFileDownloadResponse>(startRequest);

            if (startResponse == null)
                throw new NullReferenceException(nameof(startResponse));


            if (File.Exists(Path.Combine(Directory.GetCurrentDirectory(), "Files", fileName)))
                File.Delete(Path.Combine(Directory.GetCurrentDirectory(), "Files", fileName));

            if (TempFile.IsExist())
                TempFile.Delete();
            TempFile.Create(startResponse.Chunks, 0, startResponse.FileKey!, _endPointServer.ToString()!);

            Stopwatch sw = Stopwatch.StartNew();
            int recievedBytes = 0;
            if (startResponse.Chunks > 0)
            {
                for (int i = 0; i < startResponse.Chunks; i++)
                {
                    int startChunk = i;
                    long left = startResponse.Chunks - i;
                    byte windowSize = 10;
                    if (left < windowSize)
                        windowSize = (byte)left;
                    var windowStart = new FileWindowStart();
                    windowStart.ChunkCount = windowSize;
                    windowStart.StartChunk = startChunk;
                    windowStart.FileKey = startResponse.FileKey;
                    SyncNetworkingHelpers.SendPacket(_mainSocket, windowStart, _endPointServer);

                    List<byte[]> tempBytes = new();
                    int j;
                    PacketBase? packet = null;
                    for (j = 0; j < windowSize; j++)
                    {
                        packet = SyncNetworkingHelpers.ReceivePacket(_mainSocket, ref _buffer, _resolver, ref _endPointServer);
                        if (packet is DownloadFileResponse dfResponse)
                        {
                            tempBytes.Add(dfResponse.Data!);
                            packet = null;
                        }
                        else
                            break;
                    }

                    if (packet == null)
                    {
                        packet = SyncNetworkingHelpers.ReceivePacket(_mainSocket, ref _buffer, _resolver, ref _endPointServer);
                    }

                    bool needContinue = false;
                    if (packet is FileWindowEnd fweRequest)
                    {
                        needContinue = j == windowSize;
                    }

                    if (needContinue)
                    {
                        i += windowSize - 1;
                        int k = startChunk;
                        foreach (var item in tempBytes)
                        {
                            recievedBytes += item.Length;
                            TempFile.Add(k + 1, item);
                            k++;
                        }

                    }
                    else
                        i = startChunk - 1;
                }
            }
            else
            {
                ConsoleHelpers.LogError(System.Text.Encoding.UTF8.GetString(startResponse!.FileKey!));
                return;
            }
            sw.Stop();
            ConsoleHelpers.LogNotify($"Bitrate is {(float)recievedBytes / (float)sw.ElapsedMilliseconds / 1000f} MB/s");

            string path = System.Text.Encoding.UTF8.GetString(startResponse!.FileKey!);
            path = Path.Combine(Directory.GetCurrentDirectory(), "Files", path);
            TempFile.Finish(path);
            ConsoleHelpers.LogNotify($"File will saved to {path}");

            if (OperatingSystem.IsWindows())
            {
                ConsoleHelpers.LogSuccess("File downloaded! Open? (y/n)", typeof(SyncUdpClient).ToString(), true);

                if (Console.ReadLine() == "y")
                {
                    string cmd = "explorer.exe";
                    string arg = "/select, " + path;
                    Process.Start(cmd, arg);
                }
            }
        }

        private void CreateDownloadRequest()
        {
            Console.WriteLine("Enter filename");
            RequestDownload(Console.ReadLine() ?? string.Empty);
        }

        private void CreateEchoRequest()
        {
            string msg;

            while (true)
            {
                Console.WriteLine("Enter message to echo:");
                msg = Console.ReadLine()!;

                if (!string.IsNullOrEmpty(msg))
                    break;

                Console.WriteLine("message should not be empty");
            }

            var request = new EchoRequest();
            request.Message = msg;

            var response = RequestServer<EchoResponse>(request);

            if (response == null)
            {
                ConsoleHelpers.LogError($"Response is not received");
                throw new Exception("unexpected response received");
            }

            Console.WriteLine($"ECHO response: {response.EchoMessage}");
        }
        private void CreateTimeRequest()
        {
            var request = new TimeRequest();
            var response = RequestServer<TimeResponse>(request);

            if (response == null)
            {
                ConsoleHelpers.LogError($"Response is not received");
                throw new Exception("unexpected response received");
            }

            Console.WriteLine($"TIME response: {response.TimeMessage}");
        }

        private void SendMessage(PacketBase message)
        {
            SyncNetworkingHelpers.SendPacket(_mainSocket, message, _endPointServer);
        }

        /// <returns>response from server</returns>
        private T? RequestServer<T>(PacketBase request) where T : PacketBase
        {
            SyncNetworkingHelpers.SendPacket(_mainSocket, request, _endPointServer);
            var raw = SyncNetworkingHelpers.ReceivePacket(_mainSocket, ref _buffer, _resolver, ref _endPointServer);

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
        // ~SyncUdpClient()
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
