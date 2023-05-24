namespace NetworkPackets
{
    public interface IEncodable
    {
        public void Encode(BinaryWriter bw);
        public void Decode(BinaryReader br);
    }
}