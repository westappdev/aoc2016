using System;
using System.Collections.Generic;
using System.IO;

namespace AdventOfCode2016 {
   class Day3 {
      private static readonly string[] Delimeter = new string[] { " " };
      private static int _possible;

      public static void Process() {
         var inputFile = File.ReadAllText(Path.Combine("Inputs", "Day3a.txt")).Replace("\r", "").Split('\n');

         RowProcess(inputFile);
         Console.WriteLine("Possible = " + _possible);
         ColumnProcess(inputFile);
         Console.WriteLine("Possible = " + _possible);
      }

      private static void RowProcess(IEnumerable<string> inputFile) {
         _possible = 0;

         foreach (var line in inputFile) {
            
            var side = line.Split(Delimeter, StringSplitOptions.RemoveEmptyEntries);

            if ((Convert.ToInt32(side[0]) + Convert.ToInt32(side[1])) > Convert.ToInt32(side[2]) 
                  && (Convert.ToInt32(side[1]) + Convert.ToInt32(side[2])) > Convert.ToInt32(side[0])
                  && (Convert.ToInt32(side[0]) + Convert.ToInt32(side[2])) > Convert.ToInt32(side[1])) {
               ++_possible;
            }
         }
      }

      private static void ColumnProcess(IEnumerable<string> inputFile) {
         var columnSet = new List<string[]>();
         var counter = 0;
         _possible = 0;

         foreach (var line in inputFile) {
            columnSet.Add(line.Split(Delimeter, StringSplitOptions.RemoveEmptyEntries));
            ++counter;

            if (counter != 3)
               continue;
            for (var row = 0; row < 3; ++row) {
               if ((Convert.ToInt32(columnSet[0][row]) + Convert.ToInt32(columnSet[1][row])) > Convert.ToInt32(columnSet[2][row])
                   && (Convert.ToInt32(columnSet[1][row]) + Convert.ToInt32(columnSet[2][row])) > Convert.ToInt32(columnSet[0][row])
                   && (Convert.ToInt32(columnSet[0][row]) + Convert.ToInt32(columnSet[2][row])) > Convert.ToInt32(columnSet[1][row])) {
                  ++_possible;
               }
            }
            columnSet.Clear();
            counter = 0;
         }
      }
   }
}
/*--- Day 3: Squares With Three Sides ---

Now that you can think clearly, you move deeper into the labyrinth of hallways and office furniture that makes up this part of Easter Bunny HQ. This must be a graphic design department; the walls are covered in specifications for triangles.

Or are they?

The design document gives the side lengths of each triangle it describes, but... 5 10 25? Some of these aren't triangles. You can't help but mark the impossible ones.

In a valid triangle, the sum of any two sides must be larger than the remaining side. For example, the "triangle" given above is impossible, because 5 + 10 is not larger than 25.

In your puzzle input, how many of the listed triangles are possible?

Your puzzle answer was 1032.

--- Part Two ---

Now that you've helpfully marked up their design documents, it occurs to you that triangles are specified in groups of three vertically. Each set of three numbers in a column specifies a triangle. Rows are unrelated.

For example, given the following specification, numbers with the same hundreds digit would be part of the same triangle:

101 301 501
102 302 502
103 303 503
201 401 601
202 402 602
203 403 603
In your puzzle input, and instead reading by columns, how many of the listed triangles are possible?

Your puzzle answer was 1838.
*/
