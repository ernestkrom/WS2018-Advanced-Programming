using System;
using System.IO;

namespace mytar
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            string ops, dest, src;

            try
            {
                ops = args[0];
                dest = args[1];
                src = Directory.GetCurrentDirectory();

                switch (ops)
                {
                    case "--store":
                        string contents="";
                        foreach (string file in Directory.EnumerateFiles(src, "*.bin"))
                        {
                            Console.WriteLine(file);
                            contents = File.ReadAllText(file);
                        }
                        //Console.WriteLine((contents));
                        break;
                    case "--restore":
                        break;
                    default:
                        invokeManual();
                        break;
                }
            }
            catch (Exception e)
            {
                invokeManual();
            }
        }

        private static void invokeManual()
        {
            // @ indicates a verbatim string literal in this instance
            Console.WriteLine(@"USAGE: mytar [--store|--restore|--help] dest src {src}
    --store:    packs all src into [dest]
    --restore:  unpacks all files stored in [dest] into the current directory
    --help:     this screen");
        }
    }
}