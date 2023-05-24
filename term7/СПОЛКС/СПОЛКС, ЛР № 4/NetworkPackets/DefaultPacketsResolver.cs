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
            int pnum = br.ReadInt32();

            return pid switch
            {
                -1 => new ExitMessage(pnum),
                0 => new StartMessage(pnum),

                1 => new EchoRequest(pnum),
                2 => new EchoResponse(pnum),

                3 => new TimeRequest(pnum),
                4 => new TimeResponse(pnum),

                8 => new UploadFileMessage(pnum),

                //10 => new DownloadFileRequest(),
                //11 => new DownloadFileResponse(),

                //12 => new DownloadFileAuthorizedRequest(pnum),
                //13 => new DownloadFileAuthorizedResponse(pnum),

                //14 => new FullFileMessage(),
                //15 => new BigFileChunkMessage(),

                20 => new GetDownloadableFilesListRequest(pnum),
                21 => new ViewServerFilesResponse(pnum),

                22 => new StartFileDownloadRequest(pnum),
                23 => new StartFileDownloadResponse(pnum),

                24 => new DownloadFileRequest(pnum),
                25 => new DownloadFileResponse(pnum),

                30 => new FileWindowStart(pnum),
                31 => new FileWindowEnd(pnum),

                _ => throw new Exception($"unknown packet id: {pid}"),
            };
        }
    }
}