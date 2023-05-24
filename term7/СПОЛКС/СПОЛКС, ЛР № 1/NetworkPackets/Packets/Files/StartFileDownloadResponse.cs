using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkPackets.Packets.Files
{
    public class StartFileDownloadResponse : PacketBase
    {
        public override int PacketID => 23;

        public long Chunks { get; set; }
        public byte[]? FileKey { get; set; }


        public StartFileDownloadResponse()
        {

        }


        public override void Decode(BinaryReader br)
        {
            Chunks = br.ReadInt64();
            int keySize = br.ReadInt32();
            FileKey = br.ReadBytes(keySize);
        }

        public override void Encode(BinaryWriter bw)
        {
            bw.Write(Chunks);
            bw.Write(FileKey!.Length);
            bw.Write(FileKey);
        }
    }
}
