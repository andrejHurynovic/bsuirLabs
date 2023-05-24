using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Shared
{
    public class Connection
    {
        private readonly Socket _socket;
        private readonly byte[] _buffer;
        private readonly EndPoint _endPoint;

        public Socket Socket { get => _socket; }
        public byte[] Buffer { get => _buffer; }
        public EndPoint EndPoint { get => _endPoint; }

        public Connection(Socket socket, int size)
        {
            _socket = socket;
            _buffer = new byte[size];
        }

        public Connection(Socket socket, EndPoint endPoint)
        {
            _socket = socket;
            _endPoint = endPoint;
        }

        public bool FindWithEndpoint(Connection connection)
        {
            return connection.EndPoint == EndPoint;
        }
    }
}
