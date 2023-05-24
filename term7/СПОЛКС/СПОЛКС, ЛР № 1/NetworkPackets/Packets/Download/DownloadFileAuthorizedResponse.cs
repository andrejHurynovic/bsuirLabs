using NetworkPackets.Packets.Deprecated;

namespace NetworkPackets.Packets.Download
{
    public class DownloadFileAuthorizedResponse : PacketBase
    {
        public enum FailReasons
        {
            None,
            WrongKey,
            OutdatedKey,
            Other,
        }


        public override int PacketID => 13;

        public bool Result { get; set; }
        public FailReasons FailReason { get; set; }

        //public FileTransportingInfo? FileTransportingInfo { get; set; }

        public long FileSize { get; set; }


        public override void Decode(BinaryReader br)
        {
            Result = br.ReadBoolean();

            if (!Result)
            {
                FailReason = (FailReasons)br.ReadInt32();
                return;
            }

            //FileTransportingInfo = br.ReadEncodable<FileTransportingInfo>();
            FileSize = br.ReadInt64();
        }

        public override void Encode(BinaryWriter bw)
        {
            bw.Write(Result);

            if (!Result)
            {
                bw.Write((int)FailReason);
                return;
            }

            //bw.WriteEncodable(FileTransportingInfo!);
            bw.Write(FileSize);
        }
    }
}