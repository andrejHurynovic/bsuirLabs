namespace NetworkPackets.Packets.Deprecated
{
    [Obsolete(null, true)]
    public class FullFileMessage : PacketBase
    {
        public override int PacketID => throw new NotSupportedException();

        public byte[]? Data { get; set; }


        public FullFileMessage()
        {

        }


        public override void Decode(BinaryReader br)
        {
            int dataLength = br.ReadInt32();
            Data = br.ReadBytes(dataLength);
        }

        public override void Encode(BinaryWriter bw)
        {
            if (Data == null)
                throw new NullReferenceException(nameof(Data));

            bw.Write(Data.Length);
            bw.Write(Data);
        }
    }
}