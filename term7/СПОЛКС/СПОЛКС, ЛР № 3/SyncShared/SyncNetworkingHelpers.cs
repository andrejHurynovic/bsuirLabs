using ConsoleSugar;
using NetworkPackets;
using System.Net;
using System.Net.Sockets;

namespace SyncShared
{
    public static class SyncNetworkingHelpers
    {
        public static void SendPacket(Socket handler, PacketBase packet, EndPoint? to = null)
        {
            var ms = new MemoryStream();
            var bw = new BinaryWriter(ms);
            bw.Write(0);
            bw.Write(packet.PacketID);
            bw.Write(packet.CurrentPacketNumber);
            packet.Encode(bw);
            var endP = ms.Position;
            ms.Position = 0;
            bw.Write((int)endP - sizeof(int));
            ms.Position = endP;
            SendBytes(handler, ms, to);
            bw.Dispose();
        }

        public static void SendBytes(Socket handler, MemoryStream stream, EndPoint? to = null)
        {
            if (to == null)
                handler.Send(stream.GetBuffer(), (int)stream.Position, SocketFlags.None);
            else
                handler.SendTo(stream.GetBuffer(), (int)stream.Position, SocketFlags.None, to!);
        }

        public static void ReceiveBytes(Socket handler, byte[] buffer, int count)
        {
            int bytesLeft = count;

            while (bytesLeft > 0)
            {
                bytesLeft -= handler.Receive(new Span<byte>(buffer, count - bytesLeft, bytesLeft));
            }

            if (bytesLeft < 0)
            {
                ConsoleHelpers.LogError($"received more bytes than requested ({bytesLeft}, {count})");
            }
        }

        public static int ReceiveBytes(Socket handler, ref byte[] buffer, int count, ref EndPoint from)
        {
            buffer = new byte[buffer.Length];
            return handler.ReceiveFrom(buffer, ref from);
        }

        public static PacketBase ReceivePacket(Socket handler, byte[] buffer, IPacketsResolver resolver)
        {
            ReceiveBytes(handler, buffer, sizeof(int));
            int size = BitConverter.ToInt32(buffer);
            ReceiveBytes(handler, buffer, size);
            return resolver.DecodePacket(buffer, size);
        }

        public static PacketBase ReceivePacket(Socket handler, ref byte[] buffer, IPacketsResolver resolver, ref EndPoint from)
        {
            int size = ReceiveBytes(handler, ref buffer, buffer.Length, ref from) - sizeof(int);
            for (int i = sizeof(int); i < sizeof(int) + size; i++)
            {
                buffer[i - sizeof(int)] = buffer[i];
            }
            return resolver.DecodePacket(buffer, size);
        }
    }
}