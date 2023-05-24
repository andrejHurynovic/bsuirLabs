using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkPackets.Packets.Files
{
    public class DownloadFileRequest : PacketBase
    {
        public override int PacketID => 24;

        public long NeededChunk { get; set; }
        public byte[]? FileKey { get; set; }


        public DownloadFileRequest()
        {

        }


        public override void Decode(BinaryReader br)
        {
            NeededChunk = br.ReadInt64();
            var keySize = br.ReadInt32();
            FileKey = br.ReadBytes(keySize);
        }

        public override void Encode(BinaryWriter bw)
        {
            bw.Write(NeededChunk);
            bw.Write(FileKey!.Length);
            bw.Write(FileKey);
        }
    }
}
