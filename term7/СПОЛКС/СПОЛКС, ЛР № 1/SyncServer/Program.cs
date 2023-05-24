using SynchronousServer;

Console.WriteLine("Privet, mir!");
int port = 25565;

Console.WriteLine("Enter port:");
for (; !int.TryParse(Console.ReadLine(), out port);)
{
    Console.WriteLine("Parsing failed. Try again.");
}

string fileFolders = Path.Combine(Directory.GetCurrentDirectory(), "Files");
var server = new SyncTcpServer(port, fileFolders, 50);
server.Start();

Console.WriteLine("press any key to exit...");
Console.ReadLine();
Console.WriteLine("Dotvidaninya, mir!");