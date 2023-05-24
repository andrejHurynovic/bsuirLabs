using SynchronousServer;

int port = 25565;

Console.WriteLine("Enter port:");
for (; !int.TryParse(Console.ReadLine(), out port);)
{
    Console.WriteLine("Parsing failed. Try again.");
}

Console.WriteLine("Choose protocol: TCP; UDP;");
string protocol = string.Empty;
do
{
    protocol = Console.ReadLine();
} while (!protocol.Contains("UDP", StringComparison.OrdinalIgnoreCase) && !protocol.Contains("TCP", StringComparison.OrdinalIgnoreCase));

string fileFolders = Path.Combine(Directory.GetCurrentDirectory(), "Files");

if (protocol.Contains("UDP", StringComparison.OrdinalIgnoreCase))
{
    var server = new SyncUdpServer(port, fileFolders);
    server.Start();
}
else
{
    var server = new SyncTcpServer(port, fileFolders);
    server.Start();
}