﻿namespace NetworkPackets.Packets.Echo
{
    public class EchoRequest : PacketBase
    {
        public override int PacketID => 1;

        public string? Message { get; set; }


        public EchoRequest()
        {

        }


        public override void Decode(BinaryReader br)
        {
            Message = br.ReadString();
        }

        public override void Encode(BinaryWriter bw)
        {
            bw.Write(Message ?? string.Empty);
        }
    }
}