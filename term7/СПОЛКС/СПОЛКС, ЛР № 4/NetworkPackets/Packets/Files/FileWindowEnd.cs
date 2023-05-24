using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkPackets.Packets.Files
{
    public class FileWindowEnd : PacketBase
    {
        public override int PacketID => 31;

        public FileWindowEnd():base()
        {

        }

        public FileWindowEnd(int currentPacketNumber) : base(currentPacketNumber)
        {

        }

        public override void Encode(BinaryWriter bw)
        {
            
        }

        public override void Decode(BinaryReader br)
        {

        }
    }
}
