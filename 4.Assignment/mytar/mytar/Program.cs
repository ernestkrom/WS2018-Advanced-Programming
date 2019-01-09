using System;

namespace mytar
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            // @ indicates a verbatim string literal in this instance
            string man = @"USAGE: mytar [--store|--restore|--help] dest src {src}
    --store:    packs all src into [dest]
    --restore:  unpacks all files stored in [dest] into the current directory
    --help:     this screen";

            if (args.Length != 0)
            {
                try
                {
                    string argument = args[0];
                    string destination = args[1];
                    string source = args[2];
                }
                
                // input for archiving is current directory
                // unpack into current directory --> src for extraction can be anywhere
            }
            else
            {
                Console.WriteLine(man);
            }
        }
    }
}