using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdventOfCode2016
{
   class Day1
   {
      public static void Process()
      {
         var xposition = 0;
         var yposition = 0;
         HashSet<String> vectors = new HashSet<string>();
         vectors.Add("0,0");

         FindPosition(ref xposition, ref yposition, vectors);

         Console.WriteLine("Ending position x = " + xposition + " y = " + yposition);
         Console.WriteLine("Resulting distance from the Easter Bunny = " + (Math.Abs(xposition) + Math.Abs(yposition)));
      }

      private static void AddPoint(int xpos, int ypos, int move, int xmove, HashSet<String> vectors) {
         for (var count = 0; count < move ; ++count) {
            if (xmove == 0) {
               if (vectors.Contains(xpos + "," + (ypos + count))) {
                  Console.WriteLine("Intersection at " + xpos + "," + (ypos + count) + " Distance from home = " + (Math.Abs(xpos) + Math.Abs(ypos + count)));
               }
               vectors.Add(xpos + "," + (ypos + count));
            }
            else if (xmove == 1) {
               if (vectors.Contains((xpos + count) + "," + ypos))
               {
                  Console.WriteLine("Intersection at " + (xpos + count) + "," + ypos + " Distance from home = " + (Math.Abs(xpos + count) + Math.Abs(ypos)));
               }
               vectors.Add((xpos + count) + "," + ypos);
            }
         }
      }

      private static void FindPosition(ref int xpos, ref int ypos, HashSet<String> vectors) {
         var inputFile = File.ReadAllText(Path.Combine("Inputs", "Day1a.txt")).Replace("\r", "").Replace("\n", "").Replace(" ", "").Split(',');
         var position = 0;
         
         foreach (var move in inputFile) {

            if (move.Substring(0, 1).Equals("R", StringComparison.InvariantCultureIgnoreCase)) {

               switch (position) {
                  case 0: // North
                     AddPoint(xpos, ypos, Convert.ToInt32(move.Substring(1, move.Length - 1)), 1, vectors);
                     xpos += Convert.ToInt32(move.Substring(1, move.Length - 1));
                     position = 1;
                     break;
                  case 1: // East
                     AddPoint(xpos, ypos, -(Convert.ToInt32(move.Substring(1, move.Length - 1))), 0, vectors);
                     ypos -= Convert.ToInt32(move.Substring(1, move.Length - 1));
                     position = 2;
                     break;
                  case 2: // South
                     AddPoint(xpos, ypos, -(Convert.ToInt32(move.Substring(1, move.Length - 1))), 1, vectors);
                     xpos -= Convert.ToInt32(move.Substring(1, move.Length - 1));
                     position = 3;
                     break;
                  case 3: // West
                     AddPoint(xpos, ypos, Convert.ToInt32(move.Substring(1, move.Length - 1)), 0, vectors);
                     ypos += Convert.ToInt32(move.Substring(1, move.Length - 1));
                     position = 0;
                     break;
               }
            }
            else if (move.Substring(0, 1).Equals("L", StringComparison.CurrentCultureIgnoreCase)) {
               switch (position) {
                  case 0: // North
                     AddPoint(xpos, ypos, -(Convert.ToInt32(move.Substring(1, move.Length - 1))), 1, vectors);
                     xpos -= Convert.ToInt32(move.Substring(1, move.Length - 1));
                     position = 3;
                     break;
                  case 1: // East
                     AddPoint(xpos, ypos, Convert.ToInt32(move.Substring(1, move.Length - 1)), 0, vectors);
                     ypos += Convert.ToInt32(move.Substring(1, move.Length - 1));
                     position = 0;
                     break;
                  case 2: // South
                     AddPoint(xpos, ypos, Convert.ToInt32(move.Substring(1, move.Length - 1)), 1, vectors);
                     xpos += Convert.ToInt32(move.Substring(1, move.Length - 1));
                     position = 1;
                     break;
                  case 3: // West
                     AddPoint(xpos, ypos, -(Convert.ToInt32(move.Substring(1, move.Length - 1))), 0, vectors);
                     ypos -= Convert.ToInt32(move.Substring(1, move.Length - 1));
                     position = 2;
                     break;
               }
            }
         }
      }
   }
}

/*
--- Day 1: No Time for a Taxicab ---

Santa's sleigh uses a very high-precision clock to guide its movements, and the clock's oscillator is regulated by stars.Unfortunately, the stars have been stolen...by the Easter Bunny.To save Christmas, Santa needs you to retrieve all fifty stars by December 25th.

Collect stars by solving puzzles.Two puzzles will be made available on each day in the advent calendar; the second puzzle is unlocked when you complete the first.Each puzzle grants one star. Good luck!


You're airdropped near Easter Bunny Headquarters in a city somewhere. "Near", unfortunately, is as close as you can get - the instructions on the Easter Bunny Recruiting Document the Elves intercepted start here, and nobody had time to work them out further.


The Document indicates that you should start at the given coordinates (where you just landed) and face North.Then, follow the provided sequence: either turn left(L) or right(R) 90 degrees, then walk forward the given number of blocks, ending at a new intersection.

There's no time to follow such ridiculous instructions on foot, though, so you take a moment and work out the destination. Given that you can only walk on the street grid of the city, how far is the shortest path to the destination?

For example:

Following R2, L3 leaves you 2 blocks East and 3 blocks North, or 5 blocks away.
R2, R2, R2 leaves you 2 blocks due South of your starting position, which is 2 blocks away.
R5, L5, R5, R3 leaves you 12 blocks away.
How many blocks away is Easter Bunny HQ?

Your puzzle answer was 301.

The first half of this puzzle is complete! It provides one gold star: *

--- Part Two ---

Then, you notice the instructions continue on the back of the Recruiting Document.Easter Bunny HQ is actually at the first location you visit twice.

For example, if your instructions are R8, R4, R4, R8, the first location you visit twice is 4 blocks away, due East.

How many blocks away is the first location you visit twice? 

Puzzle Answer is 130.
*/