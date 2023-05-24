using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkPackets.Packets
{
    public class ExitMessage : PacketBase
    {
        public override int PacketID => 0;

        public override void Decode(BinaryReader br)
        {
            
        }

        public override void Encode(BinaryWriter bw)
        {
            
        }
    }
}
