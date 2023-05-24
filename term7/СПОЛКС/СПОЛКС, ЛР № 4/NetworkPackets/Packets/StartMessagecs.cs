using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkPackets.Packets
{
    public class StartMessage : PacketBase
    {
        public override int PacketID => 0;

        public int Port { get; set; }

        public StartMessage() : base()
        {

        }

        public StartMessage(int currentPacketNumber) : base(currentPacketNumber)
        {

        }


        public override void Decode(BinaryReader br)
        {
            Port = br.ReadInt32();
        }

        public override void Encode(BinaryWriter bw)
        {
            bw.Write(Port);
        }
    }
}
