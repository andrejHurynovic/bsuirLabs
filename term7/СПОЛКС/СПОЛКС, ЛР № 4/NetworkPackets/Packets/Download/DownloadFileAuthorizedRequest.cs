namespace NetworkPackets.Packets.Download
{
    public class DownloadFileAuthorizedRequest : PacketBase
    {
        public override int PacketID => 12;

        public byte[]? Key { get; set; }
        public ulong Offset { get; set; }


        public DownloadFileAuthorizedRequest() : base()
        {

        }

        public DownloadFileAuthorizedRequest(int currentPacketNumber) : base(currentPacketNumber)
        {

        }


        public override void Decode(BinaryReader br)
        {
            int keyLength = br.ReadInt32();
            Key = br.ReadBytes(keyLength);
            Offset = br.ReadUInt64();
        }

        public override void Encode(BinaryWriter bw)
        {
            if (Key == null)
                throw new NullReferenceException(nameof(Key));

            bw.Write(Key.Length);
            bw.Write(Key);
            bw.Write(Offset);
        }
    }
}