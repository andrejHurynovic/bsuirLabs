using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shared
{
    public static class FileChunker
    {
        public static long FileChunkSize { get { return ushort.MaxValue - 1000; } }

        public static long GetFileChunksCount(FileInfo? finfo)
        {
            return finfo!.Length / FileChunkSize + 1;
        }

        public static byte[] GetChunk(FileInfo finfo, long chunk)
        {
            FileStream fstream = finfo.OpenRead();
            fstream.Position = chunk * FileChunkSize;
            var left = fstream.Length - fstream.Position;
            byte[] buffer;

            if (left < FileChunkSize)
                buffer = new byte[left];
            else
                buffer = new byte[FileChunkSize];

            fstream.Read(buffer, 0, buffer.Length);
            fstream.Close();
            return buffer;
        }
    }
}
