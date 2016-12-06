using System;
using System.IO;
using System.Text;

namespace AdventOfCode2016 {
   internal static class Day6 {
      private const int Columns = 8;

      public static void Process() {
         var messageArray = new int[26, Columns];

         var inputFile = File.ReadAllText(Path.Combine("Inputs", "Day6a.txt")).Replace("\r", "").Split('\n');

         InitializeArray(messageArray);

         foreach (var line in inputFile) {
            var charArray = line.ToCharArray();
            ++messageArray[charArray[0] - 97, 0];
            ++messageArray[charArray[1] - 97, 1];
            ++messageArray[charArray[2] - 97, 2];
            ++messageArray[charArray[3] - 97, 3];
            ++messageArray[charArray[4] - 97, 4];
            ++messageArray[charArray[5] - 97, 5];
            ++messageArray[charArray[6] - 97, 6];
            ++messageArray[charArray[7] - 97, 7];
         }

         Console.WriteLine("Most common Passcode = " + MostCommonCharacter(messageArray));
         Console.WriteLine("Least common Passcode = " + LeastCommonCharacter(messageArray));
      }

      private static string MostCommonCharacter(int[,] messageArray) {
         var result = new StringBuilder();

         for (var col = 0; col < Columns; ++col) {
            var index = 0;
            var row = 0;
            var priorCount = 0;

            for (; row < 26; ++row) {
               if (messageArray[row, col] <= priorCount)
                  continue;
               index = row;
               priorCount = messageArray[row, col];
            }
            result.Append((char)(index + 97));
         }

         return result.ToString();
      }

      private static string LeastCommonCharacter(int[,] messageArray) {
         var result = new StringBuilder();

         for (var col = 0; col < Columns; ++col) {
            var index = 0;
            var row = 0;
            var priorCount = 62789;

            for (; row < 26; ++row) {
               if ((messageArray[row, col] <= 0) || (messageArray[row, col] >= priorCount))
                  continue;
               index = row;
               priorCount = messageArray[row, col];
            }
            result.Append((char)(index + 97));
         }

         return result.ToString();
      }

      private static void InitializeArray(int[,] messageArray) {
         for (var row = 0; row < 26; ++row) {
            for (var col = 0; col < Columns; ++col) {
               messageArray[row, col] = 0;
            }
         }
      }
   }
}

/*
--- Day 6: Signals and Noise ---

Something is jamming your communications with Santa. Fortunately, your signal is only partially jammed, and protocol in situations like this is to switch to a simple repetition code to get the message through.

In this model, the same message is sent repeatedly. You've recorded the repeating message signal (your puzzle input), but the data seems quite corrupted - almost too badly to recover. Almost.

All you need to do is figure out which character is most frequent for each position. For example, suppose you had recorded the following messages:

eedadn
drvtee
eandsr
raavrd
atevrs
tsrnev
sdttsa
rasrtv
nssdts
ntnada
svetve
tesnvt
vntsnd
vrdear
dvrsen
enarar
The most common character in the first column is e; in the second, a; in the third, s, and so on. Combining these characters returns the error-corrected message, easter.

Given the recording in your puzzle input, what is the error-corrected version of the message being sent?

Your puzzle answer was tzstqsua.

--- Part Two ---

Of course, that would be the message - if you hadn't agreed to use a modified repetition code instead.

In this modified code, the sender instead transmits what looks like random data, but for each character, the character they actually want to send is slightly less likely than the others. Even after signal-jamming noise, you can look at the letter distributions in each column and choose the least common letter to reconstruct the original message.

In the above example, the least common character in the first column is a; in the second, d, and so on. Repeating this process for the remaining characters produces the original message, advent.

Given the recording in your puzzle input and this new decoding methodology, what is the original message that Santa is trying to send?

Your puzzle answer was myregdnr.
*/
