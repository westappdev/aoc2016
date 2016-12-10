/*
 * Advent of Code 2016
 * Day 10 (part 1 and 2)
 */

using System;
using System.Collections.Generic;
using System.IO;

namespace adventofcode
{
    class Bot
    {
        public int Index { get; }
        public int[] Values { get; set; }
        public string LowDestination { get; set; }
        public int LowDestinationId { get; set; }
        public string HighDestination { get; set; }
        public int HighDestinationId { get; set; }
        public Bot(int index)
        {
            Index = index;
            Values = new int[2] { -1, -1 };
            LowDestination = "";
            LowDestinationId = -1;
            HighDestination = "";
            HighDestinationId = -1;
        }

        public bool SetValue(int value)
        {
            if (this.Values[0] == -1)
                this.Values[0] = value;
            else if (this.Values[1] == -1)
                this.Values[1] = value;
            else
                return false; // both values already set?

            return true;
        }
        public bool HasBothValues()
        {
            return this.Values[0] > -1 && this.Values[1] > -1;
        }

        public int GetAndClearLowValue()
        {
            int lowValueIndex = this.Values[0] > this.Values[1] ? 1 : 0;
            int lowValue = this.Values[lowValueIndex];
            this.Values[lowValueIndex] = -1;
            return lowValue;
        }

        public int GetAndClearHighValue()
        {
            int highValueIndex = this.Values[0] < this.Values[1] ? 1 : 0;
            int highValue = this.Values[highValueIndex];
            this.Values[highValueIndex] = -1;
            return highValue;
        }

        public override string ToString()
        {
            return String.Format("Bot HasBothValues={0}, LowDestination={1}, LowDestinationId={2}, HighDestination={3}, HighDestinationId={4}",
                this.HasBothValues(), this.LowDestination, this.LowDestinationId, this.HighDestination, this.HighDestinationId);
        }
    }

    class ComparisonLogEntry
    {
        public int Index { get; set; }
        public int ValueA { get; set; }
        public int ValueB { get; set; }

        public ComparisonLogEntry(int index, int valueA, int valueB)
        {
            this.Index = index;
            this.ValueA = valueA;
            this.ValueB = valueB;
        }
    }

    class bscott10
    {
        private Dictionary<int, Bot> bots = new Dictionary<int, Bot>();
        private Dictionary<int, int> outputs = new Dictionary<int, int>();
        private List<ComparisonLogEntry> comparisonLog = new List<ComparisonLogEntry>();

        public bscott10()
        {
            // precreate all the bots and outputs (pointless robots and outputs shouldn't hurt anything right?)
            for (int i = 0; i < 1000; i++)
            {
                bots.Add(i, new Bot(i));
                outputs.Add(i, -1);
            }
        }

        public Dictionary<int, int> Outputs
        {
            get { return outputs; }
        }

        public List<ComparisonLogEntry> ComparisonLog
        {
            get { return comparisonLog; }
        }

        public void DumpOutputs()
        {
            for (int i = 0; i < 1000; i++)
                if (outputs[i] != -1)
                    Console.WriteLine($"Output {i} = {outputs[i]}");
        }
        public int PerformActions()
        {
            int actionsPerformed = 0;
            foreach (KeyValuePair<int, Bot> bot in bots)
            {
                Bot pBot = bot.Value;
                // we can do something I think....
                if (pBot.HasBothValues())
                {
                    // this is overkill, but i can't think of a better way to have a public interface to fetch a specific bot by
                    // what comparisons it did.
                    comparisonLog.Add(new ComparisonLogEntry(bot.Key, pBot.Values[0], pBot.Values[1]));

                    // perform low action
                    if (pBot.LowDestination == "output")
                        outputs[pBot.LowDestinationId] = pBot.GetAndClearLowValue();
                    else if (pBot.LowDestination == "bot")
                        bots[pBot.LowDestinationId].SetValue(pBot.GetAndClearLowValue());

                    // perform high action
                    if (pBot.HighDestination == "output")
                        outputs[pBot.HighDestinationId] = pBot.GetAndClearHighValue();
                    else if (pBot.HighDestination == "bot")
                        bots[pBot.HighDestinationId].SetValue(pBot.GetAndClearHighValue());

                    actionsPerformed++;
                }
            }
            return actionsPerformed;
        }
        public void ProcessInstruction(string instruction)
        {
            string[] args = instruction.Split(new char[] { ' ' });

            int botId = -1;
            int value = -1;
            string lowDest = "";
            int lowDestId = -1;
            string highDest = "";
            int highDestId = -1;

            if (args[0] == "value")
            {
                int.TryParse(args[1], out value);
                int.TryParse(args[5], out botId);

                // set a value.
                bots[botId].SetValue(value);
            }
            else if (args[0] == "bot")
            {
                int.TryParse(args[1], out botId);

                lowDest = args[5];
                int.TryParse(args[6], out lowDestId);

                highDest = args[10];
                int.TryParse(args[11], out highDestId);

                bots[botId].LowDestination = lowDest;
                bots[botId].LowDestinationId = lowDestId;
                bots[botId].HighDestination = highDest;
                bots[botId].HighDestinationId = highDestId;
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            bscott10 day10 = new bscott10();

            string[] input = File.ReadAllLines("input_day10.txt");

            // first you process everything
            for (int i = 0; i < input.Length; i++)
                day10.ProcessInstruction(input[i]);

            // then set everything in motion
            int actions = day10.PerformActions();
            while (actions > 0)
            {
                Console.WriteLine($"Performed {actions} actions.");
                actions = day10.PerformActions();
            }

            // Part 1
            foreach (ComparisonLogEntry cle in day10.ComparisonLog)
            {
                if ((cle.ValueA == 61 && cle.ValueB == 17) ||
                    (cle.ValueA == 17 && cle.ValueB == 61))
                {
                    Console.WriteLine($"Part 1 Answer: Bot {cle.Index}");
                }
            }

            // Part 2
            int value = day10.Outputs[0] * day10.Outputs[1] * day10.Outputs[2];
            Console.WriteLine($"Part 2 Answer: {value}");

            Console.ReadLine();
        }
    }
}
