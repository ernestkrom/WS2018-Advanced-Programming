using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;

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
                src = Directory.GetCurrentDirectory() + "/src";
                dest = Directory.GetCurrentDirectory() + args[1] + "/packed";

                switch (ops)
                {
                    case "--store":
                        using (StreamWriter writetext = new StreamWriter(dest))
                        {
                            foreach (var file in Directory.GetFiles(src))
                            {
                                FileInfo info = new FileInfo(file);

                                var fileName = Path.GetFileName(info.FullName);
                                byte[] fileContent = File.ReadAllBytes(file);

                                writetext.WriteLine(fileName);
                                writetext.WriteLine(fileContent.Length);

                                foreach (var b in fileContent)
                                {
                                    writetext.WriteLine(b);
                                }
                            }
                        }

                        break;
                    case "--restore":
                        //var str = System.Text.Encoding.Default.GetString(result);

                        string[] lines = System.IO.File.ReadAllLines(dest);
                        List<IndividualFileInfos> infoList = new List<IndividualFileInfos>();

                        int pos = 0;
                        while (pos < lines.Length)
                        {
                            IndividualFileInfos info =
                                new IndividualFileInfos(lines[pos], Convert.ToInt32(lines[pos + 1]));
                            infoList.Add(info);
                            pos += Convert.ToInt32(lines[pos + 1]) + 2;
                        }

                        using (StreamWriter writetext = new StreamWriter("unpacked"))
                        {
                            foreach (var info in infoList)
                            {
                                writetext.Write(info.Name + " " + info.Length + "\n");
                            }
                        }

                        break;
                    default:
                        invokeManual();
                        break;
                }
            }
            catch (Exception e)
            {
                Console.Write(e);
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

    public struct IndividualFileInfos
    {
        public readonly string Name;
        public readonly int Length;

        public IndividualFileInfos(string name, int length)
        {
            Name = name;
            Length = length;
        }
    }
}