using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace AdventOfCode2016 {
   internal static class Day8 {
      private const int Row = 6;
      private const int Column = 50;

      private static void InitializeScreen(IDictionary<string, string> screen) {
         for (var row = 0; row < Row; ++row) {
            for (var col = 0; col < Column; ++col) {
               screen.Add((row + "," + col), " ");
            }
         }
      }

      internal static void Process() {
         var screen = new Dictionary<string, string>();

         InitializeScreen(screen);

         var inputFile = File.ReadAllText(Path.Combine("Inputs", "Day8a.txt")).Replace("\r", "").Split('\n');

         foreach (var input in inputFile) {
            var command = input.Split();

            if (command[0].Equals("rect")) {
               SetRectangle(command[1].Split('x'), screen);
            }

            else if (command[0].Equals("rotate")) {
               var position = command[2].Split('=');
               Rotate(command[1], Convert.ToInt32(position[1]), Convert.ToInt32(command[4]), screen);
            }
         }

         Console.WriteLine("Done Total lit pixels = " +  screen.Count(c => c.Value == "#"));
         Console.WriteLine("Password = ");
         for (var row = 0; row < Row; ++row) {
            for (var col = 0; col < Column; ++col) {
               Console.Write(screen[row + "," + col]);
            }
            Console.WriteLine();
         }
      }

      private static void Rotate(string axis, int position, int shift, IDictionary<string, string> screen) {

         if (axis.Equals("column")) {
            for (var count = 0; count < shift; ++count) {
               var cur = screen[(Row - 1) + "," + position];

               for (var row = 0; row < Row; ++row) {
                  var temp = screen[row + "," + position];
                  screen[row + "," + position] = cur;
                  cur = temp;
               }
            }
         }
         else if (axis.Equals("row"))
         {
            for (var count = 0; count < shift; ++count) {
               var cur = screen[position + "," + (Column - 1).ToString()];

               for (var col = 0; col < Column; ++col) {
                  var temp = screen[position + "," + col];
                  screen[position + "," + col] = cur;
                  cur = temp;
               }
            }
         }
      }

      private static void SetRectangle(IReadOnlyList<string> dim, IDictionary<string, string> screen) {
         for (var row = 0; row < Convert.ToInt32(dim[1]); ++row) {
            for (var col = 0; col < Convert.ToInt32(dim[0]); ++col) {
               screen[row + "," + col] = "#";
            }
         }
      }
   }
}

/*
--- Day 8: Two-Factor Authentication ---

You come across a door implementing what you can only assume is an implementation of two-factor authentication after a long game of requirements telephone.

To get past the door, you first swipe a keycard (no problem; there was one on a nearby desk). Then, it displays a code on a little screen, and you type that code on a keypad. Then, presumably, the door unlocks.

Unfortunately, the screen has been smashed. After a few minutes, you've taken everything apart and figured out how it works. Now you just have to work out what the screen would have displayed.

The magnetic strip on the card you swiped encodes a series of instructions for the screen; these instructions are your puzzle input. The screen is 50 pixels wide and 6 pixels tall, all of which start off, and is capable of three somewhat peculiar operations:

rect AxB turns on all of the pixels in a rectangle at the top-left of the screen which is A wide and B tall.
rotate row y=A by B shifts all of the pixels in row A (0 is the top row) right by B pixels. Pixels that would fall off the right end appear at the left end of the row.
rotate column x=A by B shifts all of the pixels in column A (0 is the left column) down by B pixels. Pixels that would fall off the bottom appear at the top of the column.
For example, here is a simple sequence on a smaller screen:

rect 3x2 creates a small rectangle in the top-left corner:

###....
###....
.......
rotate column x=1 by 1 rotates the second column down by one pixel:

#.#....
###....
.#.....
rotate row y=0 by 4 rotates the top row right by four pixels:

....#.#
###....
.#.....
rotate column x=1 by 1 again rotates the second column down by one pixel, causing the bottom pixel to wrap back to the top:

.#..#.#
#.#....
.#.....
As you can see, this display technology is extremely powerful, and will soon dominate the tiny-code-displaying-screen market. That's what the advertisement on the back of the display tries to convince you, anyway.

There seems to be an intermediate check of the voltage used by the display: after you swipe your card, if the screen did work, how many pixels should be lit?

Your puzzle answer was 115.

--- Part Two ---

You notice that the screen is only capable of displaying capital letters; in the font it uses, each letter is 5 pixels wide and 6 tall.

After you swipe your card, what code is the screen trying to display?

Your puzzle answer was EFEYKFRFIJ.
*/