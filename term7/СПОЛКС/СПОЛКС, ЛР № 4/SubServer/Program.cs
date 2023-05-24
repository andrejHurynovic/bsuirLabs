using SubServer;

int mainport = 25565;
string[] arg = Environment.GetCommandLineArgs();
for (int i = 0; i < args.Length; i++)
{
    if (arg[i] == "port")
    {
        mainport = int.Parse(arg[i + 1]);
    }
}

var subServer = new SyncSubServer(mainport, Path.Combine(Directory.GetCurrentDirectory(), "..", "Server", "Files"));
subServer.Start();

