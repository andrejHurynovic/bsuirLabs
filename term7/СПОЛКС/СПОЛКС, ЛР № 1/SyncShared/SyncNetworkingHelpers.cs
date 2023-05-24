using ConsoleSugar;
using NetworkPackets;
using System.Net.Sockets;

namespace SyncShared
{
    public static class SyncNetworkingHelpers
    {
        public static void SendPacket(Socket handler, PacketBase packet)
        {
            var ms = new MemoryStream();
            var bw = new BinaryWriter(ms);
            bw.Write(0);
            bw.Write(packet.PacketID);
            packet.Encode(bw);
            var endP = ms.Position;
            ms.Position = 0;
            bw.Write((int)endP - sizeof(int));
            ms.Position = endP;
            SendBytes(handler, ms);
            bw.Dispose();
        }

        public static void SendBytes(Socket handler, MemoryStream stream)
        {
            handler.Send(stream.GetBuffer(), (int)stream.Position, SocketFlags.None);
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

        public static PacketBase ReceivePacket(Socket handler, byte[] buffer, IPacketsResolver resolver)
        {
            ReceiveBytes(handler, buffer, sizeof(int));
            int size = BitConverter.ToInt32(buffer);
            ReceiveBytes(handler, buffer, size);
            return resolver.DecodePacket(buffer, size);
        }
    }
}