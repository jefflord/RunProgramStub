using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestCallToNetFromNative
{
    public class Class1
    {
        static int pwzMethodName(String pwzArgument)
        {
            File.AppendAllText(@"c:\temp\cxxxxxx.txt", $"{pwzArgument.ToUpper()}!!!\r\n");
            //Debugger.Launch();
            //return s.ToUpper();
            return 1000;
        }
    }
}
