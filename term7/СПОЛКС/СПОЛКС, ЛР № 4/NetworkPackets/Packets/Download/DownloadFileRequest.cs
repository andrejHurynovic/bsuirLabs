//namespace NetworkPackets.Packets.Download
//{
//    public class DownloadFileRequest : PacketBase
//    {
//        public override int PacketID => 10;

//        public string? FileName { get; set; }


//        public DownloadFileRequest()
//        {

//        }


//        public override void Decode(BinaryReader br)
//        {
//            FileName = br.ReadString();
//        }

//        public override void Encode(BinaryWriter bw)
//        {
//            bw.Write(FileName ?? string.Empty);
//        }
//    }
//}