namespace NetworkPackets.Packets.Deprecated
{
    [Obsolete(null, true)]
    public class ChunkedFileAssembler
    {
        /*
         * типа, я сначала думал, пока файл качаешь - части записываешь
         * на диск в тмп папку в тмп файл, а когда докачаешь последний
         * чанк, то типа всё читаешь, если сжато - распаковываешь
         * и получаешь типа изначальный файл, но:
         *      1) нахуя сохранять куски в тмп, если можно сразу их коллектить
         * в папку назначения;
         *      2) нахуя распаковывать, если можно оставить сжатым;
         * Бтв, CompressionMethod можно оставить, если вдруг нужно
         * распаковывать файл сразу.
         */

        public event Action<ChunkedFileAssembler> OnFileLoaded;
        //prototype
        private readonly FileStream _fStream;
        private readonly string _tmpPath;

        private long _bytesLeft;
        private FileTransportingInfo.CompressionMethods _compressionMethod;


        public ChunkedFileAssembler(FileTransportingInfo ftinfo)
        {
            _tmpPath = Path.GetTempFileName();
            _fStream = new FileStream(_tmpPath, FileMode.CreateNew, FileAccess.ReadWrite);
            _bytesLeft = ftinfo.FullLength;
            _compressionMethod = ftinfo.CompressionMethod;
        }

        public void AddChunk(BigFileChunkMessage chunkMsg)
        {
            _bytesLeft -= chunkMsg.Data!.Length;

            if (_bytesLeft < 0)
            {
                throw new Exception($"chunk or packet corrupted: {nameof(_bytesLeft)} becomes {_bytesLeft}");
            }

            _fStream.Write(chunkMsg.Data);

            if (_bytesLeft == 0)
            {
                Finish();
            }
        }

        private void Finish()
        {
            throw new NotImplementedException();
        }


    }
}