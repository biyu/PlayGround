using Microsoft.Phone.Info;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FantasticProject.Utils
{
    class FantasticDebugger
    {

        static private StackTrace stackTrace;
        public enum LogTiming { Enter, Exit };

        static public void Log()
        {
            // trick here; MUST create NEW stack ONLY in log functions
            stackTrace = new StackTrace(1, false);
            string log = GetBasicInfo();
            Debug.WriteLine(log);
        }

        static public void Log(string message)
        {
            // trick here; MUST create NEW stack ONLY in log functions
            stackTrace = new StackTrace(1, false);
            string log = GetBasicInfo() + ": " + message;
            Debug.WriteLine(log);
        }

        static public void LogWhen(LogTiming when)
        {
            // trick here; MUST create NEW stack ONLY in log functions
            stackTrace = new StackTrace(1, false);
            string log = GetBasicInfo() + ": " + (when == LogTiming.Enter ? "ENTER" : "EXIT");
            Debug.WriteLine(log);
        }

        static public void LogCurrentMemoryUsage()
        {
            FantasticDebugger.Log("Current Memory Usage: " + DeviceStatus.ApplicationCurrentMemoryUsage);
        }

        static private string GetBasicInfo()
        {
            return Emphasize(TimeStamp()) + Emphasize(ClassName()) + Emphasize(FunctionName());
        }

        static private string FunctionName()
        {
            return stackTrace.GetFrame(0).GetMethod().Name;
        }

        static private string ClassName()
        {
            // trick here to get class name
            return stackTrace.GetFrame(0).GetMethod().DeclaringType.Name;
        }

        static private string TimeStamp()
        {
            return DateTime.Now.ToString("HH:mm:ss.fff", CultureInfo.InvariantCulture);
        }

        static private string Emphasize(string message)
        {
            return "[" + message + "]";
        }
    }
}
