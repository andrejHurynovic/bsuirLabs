namespace NetworkPackets
{
    public abstract class PacketBase : IEncodable
    {
        protected static int _packetNumber = 0;
        protected int _currentPacketNumber;
        
        public int CurrentPacketNumber { get => _currentPacketNumber; }
        public abstract int PacketID { get; }


        public PacketBase()
        {
            ++_packetNumber;
            _currentPacketNumber = _packetNumber;
        }

        public PacketBase(int currentPacketNumber)
        {
            _currentPacketNumber = currentPacketNumber;
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