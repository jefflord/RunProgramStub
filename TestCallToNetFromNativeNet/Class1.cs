
namespace TestCallToNetFromNativeNet
{
    
    public class Class1
    {
        [DllExport]
        static int pwzMethodName(String pwzArgument)
        {
            File.AppendAllText(@"c:\temp\cxxxxxx.txt", $"{pwzArgument.ToUpper()}!!!\r\n");
            //Debugger.Launch();
            //return s.ToUpper();
            return 1000;
        }

        [DllExport]
        public static void ManagedFunction()
        {
            
            Console.WriteLine("Hello from managed .NET code!");
        }
    }
}
