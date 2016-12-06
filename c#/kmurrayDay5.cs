using System;
using System.Security.Cryptography;
using System.Text;

namespace AdventOfCode2016 {
   internal static class Day5 {

      public static void Process() {
         const string secretKey = "ffykfhsq";
         var number = 500000;
         var count = 8;
         var count2 = 8;
         var password = new StringBuilder();
         var password2 = new char[8];

         while (count2 > 0) {
            var result = GenerateMD5Hash(secretKey + number);

            if (result.Substring(0, 5).Equals("00000")) {
               Console.WriteLine("Number = " + number + " Hash = " + result);
               var resultArray = result.ToCharArray();

               if (count > 0) {
                  password.Append(resultArray[5]);
                  --count;
               }

               if (resultArray[5].Equals('0') && password2[0].Equals('\0')) {
                  password2[0] = resultArray[6];
                  --count2;
               } 
               else if (resultArray[5].Equals('1') && password2[1].Equals('\0')) {
                  password2[1] = resultArray[6];
                  --count2;
               } 
               else if (resultArray[5].Equals('2') && password2[2].Equals('\0')) {
                  password2[2] = resultArray[6];
                  --count2;
               } 
               else if (resultArray[5].Equals('3')&& password2[3].Equals('\0') ) {
                  password2[3] = resultArray[6];
                  --count2;
               } 
               else if (resultArray[5].Equals('4') && password2[4].Equals('\0')) {
                  password2[4] = resultArray[6];
                  --count2;
               } 
               else if (resultArray[5].Equals('5') && password2[5].Equals('\0')) {
                  password2[5] = resultArray[6];
                  --count2;
               } 
               else if (resultArray[5].Equals('6') && password2[6].Equals('\0')) {
                  password2[6] = resultArray[6];
                  --count2;
               } 
               else if (resultArray[5].Equals('7') && password2[7].Equals('\0')) {
                  password2[7] = resultArray[6];
                  --count2;
               } 
            }
            ++number;
         }
         Console.WriteLine("Program End. passcode = " + password);
         Console.WriteLine("Program End. passcode2 = " + new string(password2));
      }

      private static string GenerateMD5Hash(string key) {
         var inputBytes = Encoding.ASCII.GetBytes(key);
         var hash = MD5.Create().ComputeHash(inputBytes);

         var sb = new StringBuilder();
         foreach (var value in hash) {
            sb.Append(value.ToString("x2"));
         }

         return sb.ToString();
      }
   }
}
/*
--- Day 5: How About a Nice Game of Chess? ---

You are faced with a security door designed by Easter Bunny engineers that seem to have acquired most of their security knowledge by watching hacking movies.

The eight-character password for the door is generated one character at a time by finding the MD5 hash of some Door ID (your puzzle input) and an increasing integer index (starting with 0).

A hash indicates the next character in the password if its hexadecimal representation starts with five zeroes. If it does, the sixth character in the hash is the next character of the password.

For example, if the Door ID is abc:

The first index which produces a hash that starts with five zeroes is 3231929, which we find by hashing abc3231929; the sixth character of the hash, and thus the first character of the password, is 1.
5017308 produces the next interesting hash, which starts with 000008f82..., so the second character of the password is 8.
The third time a hash starts with five zeroes is for abc5278568, discovering the character f.
In this example, after continuing this search a total of eight times, the password is 18f47a30.

Given the actual Door ID, what is the password?

Your puzzle answer was c6697b55.

--- Part Two ---

As the door slides open, you are presented with a second door that uses a slightly more inspired security mechanism. Clearly unimpressed by the last version (in what movie is the password decrypted in order?!), the Easter Bunny engineers have worked out a better solution.

Instead of simply filling in the password from left to right, the hash now also indicates the position within the password to fill. You still look for hashes that begin with five zeroes; however, now, the sixth character represents the position (0-7), and the seventh character is the character to put in that position.

A hash result of 000001f means that f is the second character in the password. Use only the first result for each position, and ignore invalid positions.

For example, if the Door ID is abc:

The first interesting hash is from abc3231929, which produces 0000015...; so, 5 goes in position 1: _5______.
In the previous method, 5017308 produced an interesting hash; however, it is ignored, because it specifies an invalid position (8).
The second interesting hash is at index 5357525, which produces 000004e...; so, e goes in position 4: _5__e___.
You almost choke on your popcorn as the final character falls into place, producing the password 05ace8e3.

Given the actual Door ID and this new method, what is the password? Be extra proud of your solution if it uses a cinematic "decrypting" animation.

Your puzzle answer was 8c35d1ab.
*/
