﻿using System;
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
                dest = args[1];
                src = Directory.GetCurrentDirectory() + "/src";

                switch (ops)
                {
                    case "--store":
                        string contents = "";

                        foreach (var files in Directory.GetFiles(src))
                        {
                            FileInfo info = new FileInfo(files);
                            var fileName = Path.GetFileName(info.FullName);
                            var fileSize = Path.GetFileName(info.Length.ToString());

                            contents = StringToBinary(File.ReadAllText(files));

                            Console.WriteLine(fileName + " " + fileSize);
                            Console.WriteLine(contents);
                        }
                        break;
                    case "--restore":
                        //TODO Jet to be implemented
                        break;
                    default:
                        invokeManual();
                        break;
                }
            }
            catch (Exception e)
            {
                //Console.Write(e);
                invokeManual();
            }
        }

        /// <summary>
        /// https://www.fluxbytes.com/csharp/convert-string-to-binary-and-binary-to-string-in-c/
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        public static string StringToBinary(string data)
        {
            StringBuilder sb = new StringBuilder();

            foreach (char c in data.ToCharArray())
            {
                sb.Append(Convert.ToString(c, 2).PadLeft(8, '0'));
            }

            return sb.ToString();
        }

        public static string BinaryToString(string data)
        {
            List<Byte> byteList = new List<Byte>();

            for (int i = 0; i < data.Length; i += 8)
            {
                byteList.Add(Convert.ToByte(data.Substring(i, 8), 2));
            }

            return Encoding.ASCII.GetString(byteList.ToArray());
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