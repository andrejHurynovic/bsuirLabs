
int mainPort = int.Parse(Environment.GetCommandLineArgs()[0]);

var subServer = new SyncSubServer.SyncSubServer(mainPort, Path.Combine(Directory.GetCurrentDirectory(), "Files"));