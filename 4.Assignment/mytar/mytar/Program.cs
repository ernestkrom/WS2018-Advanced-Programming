using System;
using System.IO;
using System.Text;

namespace mytar
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            string ops, dest, del;

            try
            {
                ops = args[0];
                dest = Directory.GetCurrentDirectory() + "/" + args[1];
                del = ";";

                switch (ops)
                {
                    case "--store":
                        var fs = new FileStream(dest, FileMode.Create);
                        var bw = new BinaryWriter(fs);

                        for (var i = 2; i < args.Length; i++)
                        {
                            var fileHeader =
                                Encoding.ASCII.GetBytes(new FileInfo(args[i]).Length + "-" + args[i] + del);
                            var fileContent = File.ReadAllBytes(args[i]);

                            bw.Write(fileHeader);
                            bw.Write(fileContent);
                        }

                        bw.Close();
                        fs.Close();
                        break;

                    case "--restore":
                        var content = File.ReadAllBytes(args[1]);
                        var delimiter = (byte) ';';
                        var pos = 0;

                        while (pos < content.Length)
                        {
                            var header = "";
                            while (content[pos] != delimiter)
                            {
                                header += (char) content[pos];
                                pos++;
                            }

                            var temp = header.Split('-');
                            var fileSize = int.Parse(temp[0]);
                            var fileName = temp[1];
                            //write to file
                            using (var stream = new FileStream(fileName, FileMode.Create))
                            {
                                stream.Write(content, pos + 1, fileSize);
                                stream.Close();
                            }

                            pos += fileSize + 1;
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
}