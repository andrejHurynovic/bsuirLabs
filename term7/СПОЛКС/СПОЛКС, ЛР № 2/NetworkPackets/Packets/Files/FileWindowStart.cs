using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetworkPackets.Packets.Files
{
    public class FileWindowStart : PacketBase
    {
        public int ChunkCount { get; set; }
        public int StartChunk { get; set; }
        public byte[]? FileKey { get; set; }
        public override int PacketID => 30;

        public FileWindowStart() : base()
        {

        }

        public FileWindowStart(int currentPacketNumber) : base(currentPacketNumber)
        {

        }


        public override void Encode(BinaryWriter bw)
        {
            bw.Write(FileKey!.Length);
            bw.Write(FileKey);
            bw.Write(ChunkCount);
            bw.Write(StartChunk);
        }

        public override void Decode(BinaryReader br)
        {
            var keySize = br.ReadInt32();
            FileKey = br.ReadBytes(keySize);
            ChunkCount = br.ReadInt32();
            StartChunk = br.ReadInt32();
        }

    }
}
