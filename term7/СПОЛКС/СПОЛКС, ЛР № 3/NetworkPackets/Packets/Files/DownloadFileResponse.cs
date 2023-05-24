using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkPackets.Packets.Files
{
    public class DownloadFileResponse : PacketBase
    {
        public override int PacketID => 25;

        public byte[]? Data { get; set; }

        public DownloadFileResponse() : base()
        {

        }

        public DownloadFileResponse(int currentPacketNumber) : base(currentPacketNumber)
        {

        }


        public override void Decode(BinaryReader br)
        {
            var dataSize = br.ReadInt32();
            Data = br.ReadBytes(dataSize);
        }

        public override void Encode(BinaryWriter bw)
        {
            bw.Write(Data!.Length);
            bw.Write(Data);
        }
    }
}
