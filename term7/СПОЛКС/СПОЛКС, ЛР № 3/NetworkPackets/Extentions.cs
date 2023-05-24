namespace NetworkPackets
{
    public static class Extentions
    {
        public static T ReadEncodable<T>(this BinaryReader br) where T : IEncodable, new()
        {
            var v = new T();
            v.Decode(br);
            return v;
        }

        public static void WriteEncodable(this BinaryWriter bw, IEncodable encodable)
        {
            encodable.Encode(bw);
        }
    }
}