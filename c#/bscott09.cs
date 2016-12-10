/*
 * Advent of Code 2016
 * Day 9 (part 1 and 2)
 */

using System;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;

namespace adventofcode
{
    class bscott09
    {
        public static long CalcDecompressedLength(string input, bool recursive = false, int level = 0)
        {
            long decompressedLength = 0;
            MatchCollection matchCollection = Regex.Matches(input, @"\((\d+)x(\d+)\)");
            int lastMatchIndex = 0, nextCmdPosition = 0;
            int length = 0, repeatCount = 0;

            // nothing to process
            if (matchCollection.Count == 0 || level > 25)
                return input.Length;

            // pre-inline data
            if (matchCollection[0].Index > 0)
            {
                nextCmdPosition = matchCollection[0].Index;
                decompressedLength += matchCollection[0].Index;
            }

            // cycle through detected commands, ignore non-commands, include inline data
            foreach (Match m in matchCollection)
            {
                int.TryParse(m.Groups[1].Value, out length);
                int.TryParse(m.Groups[2].Value, out repeatCount);

                if (m.Index >= nextCmdPosition)
                {
                    // inline data
                    if (m.Index > nextCmdPosition)
                        decompressedLength += (m.Index - nextCmdPosition);

                    string payload = input.Substring(m.Index + m.Length, length);
                    long payloadLength = recursive ? CalcDecompressedLength(payload, true, level++) : payload.Length;

                    decompressedLength += (payloadLength * repeatCount);
                    lastMatchIndex = m.Index;
                    nextCmdPosition = (m.Index + m.Length) + length;
                }
            }

            // trailing inline data
            if (lastMatchIndex != nextCmdPosition)
                decompressedLength += (input.Length - nextCmdPosition);

            return decompressedLength;
        }

        public static string Decompress(string input, bool recursiveDecompress = false, int level = 0, int maxLevel = 25)
        {
            StringBuilder output = new StringBuilder();
            MatchCollection matchCollection = Regex.Matches(input, @"\((\d+)x(\d+)\)");
            int lastMatchIndex = 0, nextCmdPosition = 0;
            int length = 0, repeatCount = 0;

            // nothing to process or the recursion level is too high
            if (matchCollection.Count == 0 || level > maxLevel)
                return input;

            // pre-inline data
            if (matchCollection[0].Index > 0)
            {
                nextCmdPosition = matchCollection[0].Index;
                output.Append(input.Substring(0, matchCollection[0].Index));
            }

            // cycle through detected commands, ignore non-commands, include inline data
            foreach (Match m in matchCollection)
            {
                int.TryParse(m.Groups[1].Value, out length);
                int.TryParse(m.Groups[2].Value, out repeatCount);

                if (m.Index >= nextCmdPosition)
                {
                    // inline data
                    if (m.Index > nextCmdPosition)
                        output.Append(input.Substring(nextCmdPosition, m.Index - nextCmdPosition));

                    string payload = input.Substring(m.Index + m.Length, length);
                    if (recursiveDecompress)
                        payload = Decompress(payload, true, level++);

                    for (int i = 0; i < repeatCount; i++)
                        output.Append(payload);

                    lastMatchIndex = m.Index;
                    nextCmdPosition = (m.Index + m.Length) + length;
                }
            }

            // trailing inline data
            if (lastMatchIndex != nextCmdPosition)
            {
                output.Append(input.Substring(nextCmdPosition, input.Length - nextCmdPosition));
            }

            return output.ToString();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Part 1 Example Length: {0}", bscott09.CalcDecompressedLength("ADVENT"));
            Console.WriteLine("Part 1 Example Length: {0}", bscott09.CalcDecompressedLength("A(1x5)BC"));
            Console.WriteLine("Part 1 Example Length: {0}", bscott09.CalcDecompressedLength("(3x3)XYZ"));
            Console.WriteLine("Part 1 Example Length: {0}", bscott09.CalcDecompressedLength("A(2x2)BCD(2x2)EFG"));
            Console.WriteLine("Part 1 Example Length: {0}", bscott09.CalcDecompressedLength("(6x1)(1x3)A"));
            Console.WriteLine("Part 1 Example Length: {0}", bscott09.CalcDecompressedLength("X(8x2)(3x3)ABCY"));

            Console.WriteLine("Part 1 Example: {0}", bscott09.Decompress("ADVENT"));
            Console.WriteLine("Part 1 Example: {0}", bscott09.Decompress("A(1x5)BC"));
            Console.WriteLine("Part 1 Example: {0}", bscott09.Decompress("(3x3)XYZ"));
            Console.WriteLine("Part 1 Example: {0}", bscott09.Decompress("A(2x2)BCD(2x2)EFG"));
            Console.WriteLine("Part 1 Example: {0}", bscott09.Decompress("(6x1)(1x3)A"));
            Console.WriteLine("Part 1 Example: {0}", bscott09.Decompress("X(8x2)(3x3)ABCY"));

            // Part 2
            string input = File.ReadAllText("input_day09.txt").Trim();
            Console.WriteLine("Part 1 Length: {0}\n", bscott09.CalcDecompressedLength(input));
            Console.WriteLine("Part 2 Example Length: {0}", bscott09.CalcDecompressedLength("(25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN", true));

            Console.WriteLine("Part 2 Length: {0}\n", bscott09.CalcDecompressedLength(input, true));

            Console.ReadLine();
        }
    }
}
