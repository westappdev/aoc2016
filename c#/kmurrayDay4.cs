using System;
using System.IO;
using System.Linq;
using System.Text;

namespace AdventOfCode2016
{
   internal static class Day4
   {
      public static void Process()
      {
         var inputFile = File.ReadAllText(Path.Combine("Inputs", "Day4a.txt")).Replace("\r", "").Split('\n');
         var totals = 0;

         foreach (var input in inputFile)
         {
            var breakdown  = input.Split('-').ToList();
            var alphaStart = breakdown[breakdown.Count() - 1].IndexOf('[');
            var alphaEnd   = breakdown[breakdown.Count() - 1].IndexOf(']') - 1;
            var sectorId   = breakdown[breakdown.Count() - 1].Substring(0, alphaStart);
            var checksum   = breakdown[breakdown.Count() - 1].Substring(alphaStart + 1, alphaEnd - alphaStart).ToCharArray();

            var code = string.Join(" ", breakdown.Take(breakdown.Count() - 1));

            var contains = true;
            var previousCount = -1;
            var previousLetter = char.MinValue;
            var decrypted = new StringBuilder();

            //Check validity of rooms
            foreach (var letter in checksum)
            {
               var count = code.Count(c => c == letter);

               if (previousCount == -1) {
                  previousCount = count;
                  previousLetter = letter;
               }

               else if (((count == previousCount) && (letter < previousLetter)) || (count > previousCount)) {
                  contains = false;
                  break;
               }

               previousCount = count;
               previousLetter = letter;

               if (!code.Contains(letter)) {
                  contains = false;
                  break;
               }
            }
            
            //Decode room name
            foreach (var letter in code) {
               if (!letter.Equals(' ')) {
                  decrypted.Append((char)((letter - 96 + Convert.ToInt32(sectorId)) % 26 + '`'));
               }
               else {
                  decrypted.Append(letter);
               }
            }

            //Look for answer
            if (contains) {
               totals += Convert.ToInt32(sectorId);
               if (decrypted.ToString().Contains("north")) {
                  Console.WriteLine("Decrpted value = " + decrypted + " sectorid = " + sectorId);
               }
            }

            decrypted.Clear();
         }

         Console.WriteLine("Sector total = " + totals);
      }


   }
}

/*
--- Day 4: Security Through Obscurity ---

Finally, you come across an information kiosk with a list of rooms. Of course, the list is encrypted and full of decoy data, but the instructions to decode the list are barely hidden nearby. Better remove the decoy data first.

Each room consists of an encrypted name (lowercase letters separated by dashes) followed by a dash, a sector ID, and a checksum in square brackets.

A room is real (not a decoy) if the checksum is the five most common letters in the encrypted name, in order, with ties broken by alphabetization. For example:

aaaaa-bbb-z-y-x-123[abxyz] is a real room because the most common letters are a (5), b (3), and then a tie between x, y, and z, which are listed alphabetically.
a-b-c-d-e-f-g-h-987[abcde] is a real room because although the letters are all tied (1 of each), the first five are listed alphabetically.
not-a-real-room-404[oarel] is a real room.
totally-real-room-200[decoy] is not.
Of the real rooms from the list above, the sum of their sector IDs is 1514.

What is the sum of the sector IDs of the real rooms?

Your puzzle answer was 409147.

--- Part Two ---

With all the decoy data out of the way, it's time to decrypt this list and get moving.

The room names are encrypted by a state-of-the-art shift cipher, which is nearly unbreakable without the right software. However, the information kiosk designers at Easter Bunny HQ were not expecting to deal with a master cryptographer like yourself.

To decrypt a room name, rotate each letter forward through the alphabet a number of times equal to the room's sector ID. A becomes B, B becomes C, Z becomes A, and so on. Dashes become spaces.

For example, the real name for qzmt-zixmtkozy-ivhz-343 is very encrypted name.

What is the sector ID of the room where North Pole objects are stored?

Your puzzle answer was 991.
*/