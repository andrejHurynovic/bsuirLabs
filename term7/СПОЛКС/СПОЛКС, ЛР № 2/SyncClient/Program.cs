#define LOCALHOST

using ConsoleSugar;
using SynchronousClient;
using System.Net;
using System.Net.Sockets;

Console.WriteLine("Privet, mir!");
int port = 2288;
IPEndPoint? ipep;
Console.WriteLine($"enter '1' for fast EP or anyelse to manual:");

if (Console.ReadLine() == "1")
{
    const string predefedIp = "127.0.0.1";
    //"85.30.248.107";
    Console.WriteLine($"predefed ip is {predefedIp}");
    Console.WriteLine("enter port:");

    for (; !int.TryParse(Console.ReadLine(), out port);)
    {
        Console.WriteLine("Parsing failed. Try again.");
    }

    ipep = new IPEndPoint(IPAddress.Parse(predefedIp), port);
}
else
{
    for (; !IPEndPoint.TryParse(Console.ReadLine() ?? string.Empty, out ipep); Console.WriteLine("Parsing failed")) ;
}

Console.WriteLine("Choose protocol: TCP; UDP;");
string protocol = string.Empty;
do
{
    protocol = Console.ReadLine();
} while (!protocol.Contains("UDP", StringComparison.OrdinalIgnoreCase) && !protocol.Contains("TCP", StringComparison.OrdinalIgnoreCase));

if (protocol.Contains("UDP", StringComparison.OrdinalIgnoreCase))
{
    Console.WriteLine("enter local port");
    for (; !int.TryParse(Console.ReadLine(), out port);)
    {
        Console.WriteLine("Parsing failed. Try again.");
    }
}

    int tries = 0;
while (true)
{
    tries = 0;
    try
    {
        while (true)
        {
            try
            {
                if (protocol.Contains("UDP", StringComparison.OrdinalIgnoreCase))
                {
                    SyncUdpClient client = new(ipep, port);
                    client.Start();
                }
                else
                {
                    SyncTcpClient client = new(ipep);
                    client.Start();
                }
            }
            catch (Exception ex)
            {
                ConsoleHelpers.LogError($"{ex.Message}");
                tries++;
                if (tries == 5)
                {
                    throw;
                }
            }
        }
    }
    catch (Exception ex)
    {
        ConsoleHelpers.LogError($"Socket error: {ex.Message}");
        Console.WriteLine("Enter n for exit, anything else to try to reconnect");
        if ("n" == Console.ReadLine())
        {
            break;
        }
    }
}


Console.WriteLine("press any key to exit...");
Console.ReadLine();
Console.WriteLine("Dotvidaninya, mir!");
