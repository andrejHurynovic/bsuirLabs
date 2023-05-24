using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkPackets.Packets.Time
{
    public class TimeResponse : PacketBase
    {
        public override int PacketID => 4;

        public string? TimeMessage { get; set; }

        public TimeResponse() : base()
        {

        }

        public TimeResponse(int currentPacketNumber) : base(currentPacketNumber)
        {

        }


        public override void Decode(BinaryReader br)
        {
            TimeMessage = br.ReadString();
        }

        public override void Encode(BinaryWriter bw)
        {
            bw.Write(TimeMessage ?? string.Empty);
        }
    }
}
