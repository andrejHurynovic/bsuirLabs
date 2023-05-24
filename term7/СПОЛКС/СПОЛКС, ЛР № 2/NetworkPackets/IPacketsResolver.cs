using System.Runtime.CompilerServices;

namespace NetworkPackets
{
    public interface IPacketsResolver
    {
        public PacketBase GetPacket(BinaryReader br);


        public PacketBase DecodePacket(byte[] buffer, int length)
        {
            //using var ms = new MemoryStream(buffer, 0, length);
            //var br = new BinaryReader(ms);
            //var decodedPacket = GetPacket(br);
            //decodedPacket.Decode(br);
            //return decodedPacket;

            return DecodePacket(new ReadOnlyMemory<byte>(buffer, 0, length));
        }

        public unsafe PacketBase DecodePacket(ReadOnlyMemory<byte> data)
        {
             var ms = new UnmanagedMemoryStream((byte*)data.Pin().Pointer, data.Length);
            var br = new BinaryReader(ms);
            try
            {
                var decodedPacket = GetPacket(br);
                decodedPacket.Decode(br);
                return decodedPacket;
            }
            finally
            {
                br.Close();
            }
        }
    }
}