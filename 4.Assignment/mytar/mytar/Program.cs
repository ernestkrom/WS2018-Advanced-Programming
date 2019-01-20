using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
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
                        FileStream fs = new FileStream(dest, FileMode.Create);
                        BinaryWriter bw = new BinaryWriter(fs);

                        foreach (string file in Directory.EnumerateFiles(src))
                        {
                            string fname = Path.GetFileName(file);
                            long flen = new FileInfo(file).Length;
                            byte[] fcont = File.ReadAllBytes(file);

                            bw.Write(fname);
                            bw.Write(flen);
                            bw.Write(fcont);
                        }

                        bw.Close();
                        fs.Close();

                        break;
                    case "--restore":
                        FileStream fs2 = new FileStream(dest, FileMode.Open);
                        BinaryReader br = new BinaryReader(fs2);
                        List<IndFiles> list = new List<IndFiles>();
                        IndFiles indFile;

                        while (br.BaseStream.Position != br.BaseStream.Length)
                        {
                            var name = br.ReadString();
                            var len = br.ReadInt64();
                            var content = System.Text.Encoding.Default.GetString(br.ReadBytes((int) len));
                            indFile = new IndFiles(name, len, content);
                            list.Add(indFile);
                        }

                        foreach (var f in list)
                        {
                            File.WriteAllText(f.name, f.cont);
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

        struct IndFiles
        {
            public readonly string name;
            public readonly long len;
            public readonly string cont;


            public IndFiles(string name, long len, string cont)
            {
                this.name = name;
                this.len = len;
                this.cont = cont;
            }
        }
    }
}