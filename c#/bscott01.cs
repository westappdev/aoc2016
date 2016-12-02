/*
 * Advent of Code 2016
 * Day 1 (part 1)
 */
using System;
using System.Collections.Generic;

namespace adventofcode
{
    enum Direction
    {
        North,
        East,
        South,
        West
    }
    enum Side
    {
        Left = 'L',
        Right = 'R'
    }
    class Instruction
    {
        public Side Side { get; set; }
        public int StepCount { get; set; }
        public Instruction(Side side, int stepCount)
        {
            this.Side = side;
            this.StepCount = stepCount;
        }
    }
    class Point
    {
        public int X { get; set; }
        public int Y { get; set; }
        public Point(int x, int y)
        {
            this.X = x;
            this.Y = y;
        }
    }
    class bscott01
    {
        List<Instruction> instructions = new List<Instruction>();

        public void ClearInstructions()
        {
            instructions.Clear();
        }
        public bool LoadInstructions(string input)
        {
            if (input.Length == 0)
                return false;

            foreach (string s in input.Split(new char[] { ',' }))
            {
                string instruction = s.Trim().ToUpper();

                // Not a valid instruction length
                if (instruction.Length < 2)
                    continue;

                // Not a valid side
                if (instruction[0] != 'L' && instruction[0] != 'R')
                    continue;

                Side side = (Side)instruction[0];

                int stepCount = 0;
                if(!int.TryParse(instruction.Substring(1), out stepCount))
                    continue;

                instructions.Add(new Instruction(side, stepCount));
            }

            return instructions.Count > 0;
        }

        public int GetDistanceA()
        {
            int currentX = 0, currentY = 0;
            Direction currentDirection = Direction.North;

            foreach (Instruction instruction in instructions)
            {
                if (instruction.Side == Side.Left)
                    currentDirection = (int)currentDirection - 1 < 0 ? Direction.West : currentDirection - 1;
                else
                    currentDirection = (int)currentDirection + 1 > 3 ? Direction.North : currentDirection + 1;

                switch(currentDirection)
                {
                    case Direction.North:
                        currentY += instruction.StepCount;
                        break;
                    case Direction.East:
                        currentX += instruction.StepCount;
                        break;
                    case Direction.South:
                        currentY -= instruction.StepCount;
                        break;
                    case Direction.West:
                        currentX -= instruction.StepCount;
                        break;
                }
            }

            return Math.Abs(currentX) + Math.Abs(currentY);
        }
        public int GetDistanceB()
        {
            int currentX = 0, currentY = 0;
            Direction currentDirection = Direction.North;
            List<Point> history = new List<Point>();

            foreach (Instruction instruction in instructions)
            {
                if (instruction.Side == Side.Left)
                    currentDirection = (int)currentDirection - 1 < 0 ? Direction.West : currentDirection - 1;
                else
                    currentDirection = (int)currentDirection + 1 > 3 ? Direction.North : currentDirection + 1;

                for (int i = 0; i < instruction.StepCount; i++)
                {
                    switch (currentDirection)
                    {
                        case Direction.North:
                            currentY += 1;
                            break;
                        case Direction.East:
                            currentX += 1;
                            break;
                        case Direction.South:
                            currentY -= 1;
                            break;
                        case Direction.West:
                            currentX -= 1;
                            break;
                    }

                    Point point = new Point(currentX, currentY);
                    if (history.Find(value => value.X == currentX && value.Y == currentY) != null)
                        return Math.Abs(currentX) + Math.Abs(currentY);
                   history.Add(point);
                }
            }

            return 0;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            bscott01 test = new bscott01();

            // PART 1
            test.ClearInstructions();
            test.LoadInstructions("R2, L3");
            Console.WriteLine("Distance: {0}", test.GetDistanceA());

            test.ClearInstructions();
            test.LoadInstructions("R2, R2, R2");
            Console.WriteLine("Distance: {0}", test.GetDistanceA());

            test.ClearInstructions();
            test.LoadInstructions("R5, L5, R5, R3");
            Console.WriteLine("Distance: {0}", test.GetDistanceA());

            test.ClearInstructions();
            test.LoadInstructions("R3, L2, L2, R4, L1, R2, R3, R4, L2, R4, L2, L5, L1, R5, R2, R2, L1, R4, R1, L5, L3, R4, R3, R1, L1, L5, L4, L2, R5, L3, L4, R3, R1, L3, R1, L3, R3, L4, R2, R5, L190, R2, L3, R47, R4, L3, R78, L1, R3, R190, R4, L3, R4, R2, R5, R3, R4, R3, L1, L4, R3, L4, R1, L4, L5, R3, L3, L4, R1, R2, L4, L3, R3, R3, L2, L5, R1, L4, L1, R5, L5, R1, R5, L4, R2, L2, R1, L5, L4, R4, R4, R3, R2, R3, L1, R4, R5, L2, L5, L4, L1, R4, L4, R4, L4, R1, R5, L1, R1, L5, R5, R1, R1, L3, L1, R4, L1, L4, L4, L3, R1, R4, R1, R1, R2, L5, L2, R4, L1, R3, L5, L2, R5, L4, R5, L5, R3, R4, L3, L3, L2, R2, L5, L5, R3, R4, R3, R4, R3, R1");
            Console.WriteLine("Distance: {0}", test.GetDistanceA());

            // PART 2
            test.ClearInstructions();
            test.LoadInstructions("R8, R4, R4, R8");
            Console.WriteLine("Distance: {0}", test.GetDistanceB());

            test.ClearInstructions();
            test.LoadInstructions("R3, L2, L2, R4, L1, R2, R3, R4, L2, R4, L2, L5, L1, R5, R2, R2, L1, R4, R1, L5, L3, R4, R3, R1, L1, L5, L4, L2, R5, L3, L4, R3, R1, L3, R1, L3, R3, L4, R2, R5, L190, R2, L3, R47, R4, L3, R78, L1, R3, R190, R4, L3, R4, R2, R5, R3, R4, R3, L1, L4, R3, L4, R1, L4, L5, R3, L3, L4, R1, R2, L4, L3, R3, R3, L2, L5, R1, L4, L1, R5, L5, R1, R5, L4, R2, L2, R1, L5, L4, R4, R4, R3, R2, R3, L1, R4, R5, L2, L5, L4, L1, R4, L4, R4, L4, R1, R5, L1, R1, L5, R5, R1, R1, L3, L1, R4, L1, L4, L4, L3, R1, R4, R1, R1, R2, L5, L2, R4, L1, R3, L5, L2, R5, L4, R5, L5, R3, R4, L3, L3, L2, R2, L5, L5, R3, R4, R3, R4, R3, R1");
            Console.WriteLine("Distance: {0}", test.GetDistanceB());

            Console.ReadLine();
        }
    }
}
