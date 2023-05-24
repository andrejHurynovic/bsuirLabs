using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkPackets.Packets.Files
{
    public class StartFileDownloadRequest : PacketBase
    {
        public override int PacketID => 22;

        public string? FileName { get; set; }


        public StartFileDownloadRequest()
        {

        }


        public override void Decode(BinaryReader br)
        {
            FileName = br.ReadString();
        }

        public override void Encode(BinaryWriter bw)
        {
            bw.Write(FileName ?? string.Empty);
        }
    }
}
