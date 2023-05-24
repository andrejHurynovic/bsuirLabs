namespace NetworkPackets.Packets.Deprecated
{
    [Obsolete(null, true)]
    public class BigFileChunkMessage : PacketBase
    {
        public override int PacketID => 15;

        public int ChunkIndex { get; set; }
        public byte[]? Data { get; set; } // идея говно, лучше уж тупо бесконечно передавать файл


        public override void Decode(BinaryReader br)
        {
            ChunkIndex = br.ReadInt32();
            int dataLength = br.ReadInt32();
            Data = br.ReadBytes(dataLength);
        }

        public override void Encode(BinaryWriter bw)
        {
            bw.Write(ChunkIndex);
            bw.Write(Data!.Length);
            bw.Write(Data!);
        }
    }
}