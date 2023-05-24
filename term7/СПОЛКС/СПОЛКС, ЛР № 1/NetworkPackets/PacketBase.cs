namespace NetworkPackets
{
    public abstract class PacketBase : IEncodable
    {
        public abstract int PacketID { get; }


        public PacketBase()
        {

        }


        public void Pack(BinaryWriter bw)
        {
            bw.Write((int)0);

            bw.Write(PacketID);
            Encode(bw);

            var bstream = bw.BaseStream;
            var tmpP = bstream.Position;
            bstream.Position = 0;
            bw.Write(tmpP - sizeof(int));
            bstream.Position = tmpP;
        }


        public abstract void Decode(BinaryReader br);

        public abstract void Encode(BinaryWriter bw);
    }
}