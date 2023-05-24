namespace NetworkPackets.Packets.Echo
{
    public class EchoResponse : PacketBase
    {
        public override int PacketID => 2;

        public string? EchoMessage { get; set; }


        public override void Decode(BinaryReader br)
        {
            EchoMessage = br.ReadString();
        }

        public override void Encode(BinaryWriter bw)
        {
            bw.Write(EchoMessage ?? string.Empty);
        }
    }
}