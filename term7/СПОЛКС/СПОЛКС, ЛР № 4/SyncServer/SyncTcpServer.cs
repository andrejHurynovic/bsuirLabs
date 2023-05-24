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
        private readonly Socket _mainSocket;
        private readonly int _port;
        private int _nextPort;

        private bool _disposedValue;
        public SyncTcpServer(int mainPort, string fileHoldersPathes, float timeoutSeconds = 10)
        {
            _mainSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            _mainSocket.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.TcpKeepAliveInterval, 1);
            _mainSocket.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.TcpKeepAliveRetryCount, 20);
            _mainSocket.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.TcpKeepAliveTime, 5);
            _mainSocket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.KeepAlive, true);

            _port = mainPort;
            _nextPort = _port + 1;
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
                ConsoleHelpers.LogNotify($"Waiting for new connection...", typeof(SyncTcpServer).ToString(), true);
#endif
                var handler = _mainSocket.Accept();

#if CONSOLE_LOGGING_ALL
                ConsoleHelpers.LogNotify($"New connection: {handler.RemoteEndPoint}", typeof(SyncTcpServer).ToString(), true);
#endif
                HandleConnectedSocket(handler);
            }
        }

        private void HandleConnectedSocket(Socket handler)
        {
            while (true)
            {
                try
                {
                    string path = Path.Combine(Directory.GetCurrentDirectory(), "..", "SubServer", "SubServer.exe");
                    if (!File.Exists(path))
                        path = Path.Combine(Directory.GetCurrentDirectory(), "..", "..", "..", "SubServer", "bin", "Debug", "net6.0", "SubServer.exe");
                    Process.Start(Path.Combine(Directory.GetCurrentDirectory(), "..", "SubServer", "SubServer.exe"), new string[] {"port", _nextPort.ToString()});
                    var startMessage = new StartMessage();
                    startMessage.Port = _nextPort;
                    SyncNetworkingHelpers.SendPacket(handler, startMessage);
                    ConsoleHelpers.LogNotify($"Client redericted to port: {_nextPort}", typeof(SyncTcpServer).ToString(), true);
                    _nextPort++;
                    break;
                }
                catch (Exception e)
                {
                    ConsoleHelpers.LogWarning(e.Message, typeof(SyncTcpServer).ToString(), true);
                    _nextPort++;
                }
            }
        }

        private void InitAcceptingSocket()
        {
            BindAcceptingSocket();
            _mainSocket.Listen(5);
        }

        private void BindAcceptingSocket()
        {
            if (_mainSocket.IsBound)
            {
                throw new Exception("socket already bound");
            }

            _mainSocket.Bind(new IPEndPoint(IPAddress.Any, _port));


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