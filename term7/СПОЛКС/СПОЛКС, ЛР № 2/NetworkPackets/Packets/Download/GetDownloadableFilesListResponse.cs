namespace NetworkPackets.Packets.Download
{
    public class GetDownloadableFilesListResponse : PacketBase
    {
        public override int PacketID => 21;

        public string[]? FilesNames { get; set; }

        public GetDownloadableFilesListResponse() : base()
        {

        }

        public GetDownloadableFilesListResponse(int currentPacketNumber) : base(currentPacketNumber)
        {

        }

        public override void Decode(BinaryReader br)
        {
            int count = br.ReadInt32();
            var arr = new string[count];

            for (int i = -1; ++i < count;)
            {
                arr[i] = br.ReadString();
            }

            FilesNames = arr;
        }

        public override void Encode(BinaryWriter bw)
        {
            var arr = FilesNames;

            if (arr == null)
            {
                bw.Write(0);
                return;
            }

            var c = arr.Length;
            bw.Write(c);

            for (int i = -1; ++i < c;)
            {
                bw.Write(arr[i]);
            }
        }
    }
}