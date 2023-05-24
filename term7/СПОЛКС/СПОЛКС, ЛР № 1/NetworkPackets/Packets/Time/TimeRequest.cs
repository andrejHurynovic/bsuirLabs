using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkPackets.Packets.Time
{
    public class TimeRequest : PacketBase
    {
        public override int PacketID => 3;


        public TimeRequest()
        {

        }

        public override void Decode(BinaryReader br)
        {

        }

        public override void Encode(BinaryWriter bw)
        {

        }
    }
}
