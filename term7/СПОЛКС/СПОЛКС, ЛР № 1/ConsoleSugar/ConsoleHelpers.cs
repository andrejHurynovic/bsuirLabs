namespace ConsoleSugar
{
    public static class ConsoleHelpers
    {
        private class FileLogger
        {
            private readonly string _path;
            private readonly string _fileName;

            private FileStream? _fileStream;
            private BinaryWriter? _bw;


            public FileLogger(string path, string fileName)
            {
                _path = path;
                _fileName = fileName + DateTime.Now.Ticks.ToString();
            }


            public void Log(string v)
            {
                var bw = GetBinaryWriter();
                bw.Write(v);

                bw.Close();
                _bw = null;
                _fileStream = null;
            }

            public void Log(Memory<byte> data)
            {
                var fs = GetStream();
                fs.Write(data.Span);

                fs.Close();
                _fileStream = null;
            }


            private BinaryWriter GetBinaryWriter()
            {
                if (_bw == null)
                {
                    _bw = new BinaryWriter(GetStream());
                }

                return _bw;
            }

            private FileStream GetStream()
            {
                if (_fileStream == null)
                {
                    _fileStream = File.OpenWrite(Path.Combine(_path, _fileName));
                }

                return _fileStream;
            }
        }


        private const int _timeStampLength = 14; //mm:ss:ms:tttt_ (t - ticks)
        private const string _senderSeparator = ":: ";
        private static System.Text.StringBuilder? _sb;

        private static FileLogger? _fileLogger;


        static ConsoleHelpers()
        {
            DefaultForegroundColor = ConsoleColor.White;
            DefaultBackgroundColor = ConsoleColor.Black;
        }


        public static ConsoleColor DefaultForegroundColor { get; set; }
        public static ConsoleColor DefaultBackgroundColor { get; set; }


        public static void EnableLogginToFile(string path, string fileName)
        {
            _fileLogger = new FileLogger(path, fileName);
        }

        public static void DisableLoggingToFile()
        {
            _fileLogger = null;
        }


        public static void LogError(string msg, string? sender = null, bool addTimeStamp = true)
        {
            LogInternal(msg, ConsoleColor.Red, DefaultBackgroundColor, sender, addTimeStamp);
        }

        public static void LogSuccess(string msg, string? sender = null, bool addTimeStamp = true)
        {
            LogInternal(msg, ConsoleColor.Green, DefaultBackgroundColor, sender, addTimeStamp);
        }

        public static void LogWarning(string msg, string? sender = null, bool addTimeStamp = true)
        {
            LogInternal(msg, ConsoleColor.Yellow, DefaultBackgroundColor, sender, addTimeStamp);
        }

        public static void LogNotify(string msg, string? sender = null, bool addTimeStamp = true)
        {
            LogInternal(msg, ConsoleColor.Cyan, DefaultBackgroundColor, sender, addTimeStamp);
        }

        public static void Log(string msg, string? sender = null, bool addTimeStamp = true)
        {
            LogInternal(msg, ConsoleColor.Cyan, DefaultBackgroundColor, sender, addTimeStamp);
        }


        private static void LogInternal(string msg, ConsoleColor fgc, ConsoleColor bgc, string? sender, bool addTimeStamp)
        {
            if (fgc == bgc)
            {
                if (bgc == ConsoleColor.Black)
                {
                    fgc = ConsoleColor.White;
                }
                else
                {
                    bgc = ConsoleColor.Black;
                }
            }

            ConsoleColor tmpFgc = Console.ForegroundColor;
            ConsoleColor tmpBgc = Console.BackgroundColor;

            if (tmpFgc != fgc)
                Console.ForegroundColor = fgc;

            if (tmpBgc != bgc)
                Console.BackgroundColor = bgc;

            int totalLength = msg.Length + (sender != null ? (sender.Length + _senderSeparator.Length) : 0) + (addTimeStamp ? _timeStampLength : 0);

            if (totalLength == msg.Length)
            {
                Console.WriteLine(msg);
                _fileLogger?.Log(msg);
            }
            else
            {
                if (_sb == null)
                {
                    _sb = new System.Text.StringBuilder(totalLength);
                }
                else
                {
                    _sb.EnsureCapacity(totalLength);
                }

                var sb = _sb;

                if (addTimeStamp)
                {
                    var dtn = DateTime.Now;
                    sb.Append(dtn.Minute);
                    sb.Append(':');
                    sb.Append(dtn.Second);
                    sb.Append(':');
                    sb.Append(dtn.Millisecond);
                    sb.Append(':');

                    {
                        //todo: humanize tick formating
                        long ticksNum = dtn.Ticks;
                        string ticksStr = ticksNum.ToString();
                        sb.Append(ticksStr.AsSpan(ticksStr.Length - 4));
                    }

                    sb.Append(' ');
                }

                if (sender != null)
                {
                    sb.Append(sender);
                    sb.Append(_senderSeparator);
                }

                sb.Append(msg);

                var fullMsg = sb.ToString();
                Console.WriteLine(fullMsg);
                _fileLogger?.Log(fullMsg);
                sb.Clear();
            }


            if (tmpFgc != fgc)
                Console.ForegroundColor = tmpFgc;

            if (tmpBgc != bgc)
                Console.BackgroundColor = tmpBgc;
        }
    }
}