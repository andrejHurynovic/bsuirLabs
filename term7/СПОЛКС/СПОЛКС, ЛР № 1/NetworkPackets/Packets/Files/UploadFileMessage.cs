using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkPackets.Packets.Files
{
    public class UploadFileMessage : PacketBase
    {
        public override int PacketID => 8;

        public string? FileName { get; private set; }

        public UploadFileMessage()
        {
            FileName = string.Empty;
        }

        public UploadFileMessage(string fileName)
        {
            FileName = fileName;
        }

        public override void Decode(BinaryReader br)
        {
            FileName = br.ReadString();
        }

        public override void Encode(BinaryWriter bw)
        {
            bw.Write(FileName!);
        }
    }
}
