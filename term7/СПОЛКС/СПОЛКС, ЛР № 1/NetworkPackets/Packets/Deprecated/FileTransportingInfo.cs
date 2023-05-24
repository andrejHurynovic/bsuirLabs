namespace NetworkPackets.Packets.Deprecated
{
    [Obsolete("chunks are not in use", true)]
    public class FileTransportingInfo : IEncodable
    {
        public enum CompressionMethods : byte
        {
            None,
            Zip,
        }


        public long FullLength { get; set; }
        public bool Chunked { get; set; }
        public int ChunksCount { get; set; }


        public CompressionMethods CompressionMethod { get; set; }


        public void Decode(BinaryReader br)
        {
            FullLength = br.ReadInt64();
            Chunked = br.ReadBoolean();

            if (Chunked)
                ChunksCount = br.ReadInt32();

            CompressionMethod = (CompressionMethods)br.ReadByte();
        }

        public void Encode(BinaryWriter bw)
        {
            bw.Write(FullLength);
            bw.Write(Chunked);

            if (Chunked)
                bw.Write(ChunksCount);

            bw.Write((byte)CompressionMethod);
        }
    }
}