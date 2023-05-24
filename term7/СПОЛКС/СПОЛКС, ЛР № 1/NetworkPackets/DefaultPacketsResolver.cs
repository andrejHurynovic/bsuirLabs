using NetworkPackets.Packets;
using NetworkPackets.Packets.Echo;
using NetworkPackets.Packets.Download;
using NetworkPackets.Packets.Time;
using NetworkPackets.Packets.Files;

namespace NetworkPackets
{
    public class DefaultPacketsResolver : IPacketsResolver
    {
        public DefaultPacketsResolver()
        {
        }

        public PacketBase GetPacket(BinaryReader br)
        {
            int pid = br.ReadInt32();

            return pid switch
            {
                0 => new ExitMessage(),

                1 => new EchoRequest(),
                2 => new EchoResponse(),

                3 => new TimeRequest(),
                4 => new TimeResponse(),

                8 => new UploadFileMessage(),

                //10 => new DownloadFileRequest(),
                //11 => new DownloadFileResponse(),

                12 => new DownloadFileAuthorizedRequest(),
                13 => new DownloadFileAuthorizedResponse(),

                //14 => new FullFileMessage(),
                //15 => new BigFileChunkMessage(),

                20 => new GetDownloadableFilesListRequest(),
                21 => new ViewServerFilesResponse(),

                22 => new StartFileDownloadRequest(),
                23 => new StartFileDownloadResponse(),

                24 => new DownloadFileRequest(),
                25 => new DownloadFileResponse(),
                _ => throw new Exception($"unknown packet id: {pid}"),
            };
        }
    }
}