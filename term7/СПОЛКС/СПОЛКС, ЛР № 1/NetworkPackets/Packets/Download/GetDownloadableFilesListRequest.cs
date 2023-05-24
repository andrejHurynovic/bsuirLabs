namespace NetworkPackets.Packets.Download
{
    public class GetDownloadableFilesListRequest : PacketBase
    {
        public override int PacketID => 20;


        public override void Decode(BinaryReader br)
        {
        }

        public override void Encode(BinaryWriter bw)
        { 
        }
    }
}