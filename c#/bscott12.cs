/*
 * Advent of Code 2016
 * Day 12 (part 1 and 2)
 */

using System;
using System.Collections.Generic;
using System.IO;

namespace adventofcode
{
    class bscott12
    {
        private Dictionary<string, int> registers = new Dictionary<string, int>();
        private int pc = 0;

        public Dictionary<string, int> Registers
        {
            get { return registers; }
        }


        public bscott12()
        {
            for (char i = 'a'; i <= 'd'; i++)
                registers.Add(i.ToString(), 0);
        }

        public void Reset()
        {
            for (char i = 'a'; i <= 'd'; i++)
                registers[i.ToString()] = 0;
            pc = 0;
        }

        public void Process(string[] instructions)
        {
            while(pc < instructions.Length)
                ProcessInstruction(instructions[pc]);
        }

        public void ProcessInstruction(string instruction)
        {
            string[] arguments = instruction.Split(new char[] { ' ' });
            int value = 0;
            bool branch = false;

            switch (arguments[0])
            {
                case "cpy":
                    if (arguments[1][0] >= '0' && arguments[1][0] <= '9')
                        int.TryParse(arguments[1], out value);
                    else
                        value = registers[arguments[1]];

                    registers[arguments[2]] = value;
                    break;
                case "inc":
                    registers[arguments[1]]++;
                    break;
                case "dec":
                    registers[arguments[1]]--;
                    break;
                case "jnz":
                    if (arguments[1][0] >= '0' && arguments[1][0] <= '9')
                        int.TryParse(arguments[1], out value);
                    else
                        value = registers[arguments[1]];

                    int jumpOffset = int.Parse(arguments[2]);
                    if (value != 0)
                    {
                        pc = pc + jumpOffset;
                        branch = true;
                    }
                    break;
            }

            if(!branch) pc++;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            bscott12 day12 = new bscott12();

            string[] input = File.ReadAllLines("input_day12.txt");

            // part 1
            day12.Process(input);
            Console.Write("Part 1: ");
            for (char i = 'a'; i <= 'd'; i++)
                Console.Write(i.ToString() + " = " + day12.Registers[i.ToString()] + ", ");
            Console.Write("\n");

            // part 2
            day12.Reset();
            day12.Registers["c"] = 1;
            day12.Process(input);

            Console.Write("Part 2: ");
            for (char i = 'a'; i <= 'd'; i++)
                Console.Write(i.ToString() + " = " + day12.Registers[i.ToString()] + ", ");
            Console.Write("\n");

            Console.ReadLine();
        }
    }
}
