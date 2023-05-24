namespace NetworkPackets.Packets.Deprecated
{
    [Obsolete(null, true)]
    public class FileDessembler
    {
        private readonly FileStream _fStream;

        private long _bytesLeft;
        private int _chunkIndex;


        public FileDessembler(string fullPath)
        {
            var f = new FileInfo(fullPath);
            _fStream = f.OpenRead();
            _bytesLeft = f.Length;
        }


        public BigFileChunkMessage GetChunk(int chunkSize)
        {
            if (chunkSize <= 0)
                throw new ArgumentException($"should be more than zero (now: {chunkSize})", nameof(chunkSize));

            BigFileChunkMessage msg = new();
            msg.ChunkIndex = _chunkIndex;
            ++_chunkIndex;
            //msg.Data = _fStream.read
            throw new NotImplementedException();
        }
    }
}