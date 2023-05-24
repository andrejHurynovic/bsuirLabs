namespace NetworkPackets.Packets.Download
{
    public class GetDownloadableFilesListRequest : PacketBase
    {
        public override int PacketID => 20;

        public GetDownloadableFilesListRequest() : base()
        {

        }

        public GetDownloadableFilesListRequest(int currentPacketNumber) : base(currentPacketNumber)
        {

        }

        public override void Decode(BinaryReader br)
        {
        }

        public override void Encode(BinaryWriter bw)
        { 
        }
    }
}