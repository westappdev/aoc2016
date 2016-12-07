/*
 * Advent of Code 2016
 * Day 7 (Part 1 and 2)
 */

using System;
using System.Collections.Generic;
using System.IO;

namespace adventofcode
{
    class bscott07
    {
        public static int GetTLSIPCount(string[] input)
        {
            int ipCount = 0;

            for (int i = 0; i < input.Length; i++)
            {
                bool insideBracket = false;
                bool hasMirrorSequence = false;

                for (int j = 0; j < input[i].Length - 3; j++)
                {
                    if (input[i][j] == '[')
                    {
                        insideBracket = true;
                        continue;

                    }
                    else if (input[i][j] == ']')
                    {
                        insideBracket = false;
                        continue;
                    }

                    if ((input[i][j] == input[i][j + 3] && input[i][j + 1] == input[i][j + 2])
                        && (input[i][j] != input[i][j + 1] && input[i][j + 2] != input[i][j + 3]))
                        if (insideBracket)
                            break;
                        else
                            hasMirrorSequence = true;

                }

                if (!insideBracket && hasMirrorSequence)
                    ipCount++;
            }

            return ipCount;
        }

        public static int GetSSLIPCount(string[] input)
        {
            int ipCount = 0;
            for (int i = 0; i < input.Length; i++)
            {
                bool insideBracket = false;
                List<String> babSequences = new List<string>();
                List<String> abaSequences = new List<string>();
                for (int j = 0; j < input[i].Length - 2; j++)
                {
                    if (input[i][j] == '[')
                    {
                        insideBracket = true;
                        continue;

                    }
                    else if (input[i][j] == ']')
                    {
                        insideBracket = false;
                        continue;
                    }

                    if (insideBracket)
                    {
                        if (input[i][j] == input[i][j + 2] && input[i][j] != input[i][j + 1])
                            babSequences.Add(input[i].Substring(j + 1, 1) + input[i].Substring(j, 1) + input[i].Substring(j + 1, 1)); // pre flip it
                    }
                    else
                    {
                        if (input[i][j] == input[i][j + 2] && input[i][j] != input[i][j + 1])
                            abaSequences.Add(input[i].Substring(j, 3));
                    }
                }
                if (babSequences.Count > 0 && abaSequences.Count > 0)
                {
                    for (int j = 0; j < abaSequences.Count; j++)
                    {
                        if (babSequences.Contains(abaSequences[j]))
                        {
                            ipCount++;
                            break;
                        }
                    }
                }
            }
            return ipCount;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            string[] input = File.ReadAllLines("input_day07.txt");

            Console.WriteLine("Part 1 - TLS IP Count: {0}", bscott07.GetTLSIPCount(input));
            Console.WriteLine("Part 2 - SSL IP Count: {0}", bscott07.GetSSLIPCount(input));

            Console.ReadLine();
        }
    }
}
