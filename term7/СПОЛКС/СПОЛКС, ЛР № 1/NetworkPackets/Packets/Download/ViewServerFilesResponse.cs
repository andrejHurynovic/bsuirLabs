namespace NetworkPackets.Packets.Download
{
    public class ViewServerFilesResponse : PacketBase
    {
        public enum FailReasons
        {
            Other,
        }


        private byte[]? _fileNamesData;


        public override int PacketID => 21;

        public bool Result { get; set; }
        public FailReasons FailReason { get; set; }

        public string[]? FilesNames { get; set; }


        public void SetFileNamesData(byte[] data)
        {
            _fileNamesData = data;
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