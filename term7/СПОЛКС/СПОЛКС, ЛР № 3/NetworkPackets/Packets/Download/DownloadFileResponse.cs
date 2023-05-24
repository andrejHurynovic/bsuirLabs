//namespace NetworkPackets.Packets.Download
//{
//    public class DownloadFileResponse : PacketBase
//    {
//        public enum FailReasons
//        {
//            None,
//            FileNotFound,
//            AccessDenied
//        }


//        public override int PacketID => 11;
//        public bool Result { get; set; }
//        public byte[]? Key { get; set; }
//        public FailReasons FailReason { get; set; }


//        public DownloadFileResponse()
//        {

//        }


//        public override void Decode(BinaryReader br)
//        {
//            Result = br.ReadBoolean();

//            if (!Result)
//            {
//                Key = null;
//                FailReason = (FailReasons)br.ReadInt32();
//                return;
//            }

//            int keyLength = br.ReadInt32();
//            Key = br.ReadBytes(keyLength);
//        }

//        public override void Encode(BinaryWriter bw)
//        {
//            bw.Write(Result);

//            if (Result)
//            {
//                bw.Write(Key!.Length);
//                bw.Write(Key);
//            }
//            else
//            {
//                bw.Write((int)FailReason);
//            }
//        }
//    }
//}