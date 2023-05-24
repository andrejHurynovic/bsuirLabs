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


        public TimeRequest() : base()
        {

        }

        public TimeRequest(int currentPacketNumber) : base(currentPacketNumber)
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
