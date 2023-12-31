using System.Diagnostics;

namespace RunProgramStub
{
    internal class Program
    {
        static void Main(string[] args)
        {
            try
            {

                if (args.Length < 1)
                {
                    return;
                }

                // Replace "your_program.exe" with the path or name of the executable you want to run
                string programPath = args[0];


                if (programPath == "loop")
                {
                    while (true)
                    {
                        Console.WriteLine($"Still here at {DateTime.Now}");
                        Thread.Sleep(1000);
                    }
                }

                if (programPath == "loop-and-stop")
                {
                    for (var i = 0; i < 100; i++)
                    {
                        Console.WriteLine($"Still here at {DateTime.Now}");
                        Thread.Sleep(1000);
                    }
                }


                string arguments = "";

                for (var i = 1; i < arguments.Length; i++)
                {
                    arguments += $"{arguments[i]} ";
                }

                ProcessStartInfo startInfo = new ProcessStartInfo
                {
                    FileName = programPath,
                    Arguments = arguments,
                    UseShellExecute = false,
                    CreateNoWindow = true,
                    RedirectStandardOutput = true,
                    RedirectStandardError = true
                };

                Process process = new Process
                {
                    StartInfo = startInfo
                };

                process.Start();


                Console.WriteLine($"Process started successfully as {process.Id}.");
            }
            catch (Exception ex)
            {
                Console.WriteLine("An error occurred: " + ex.Message);
            }
        }
    }
}
