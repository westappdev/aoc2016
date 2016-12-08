using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace AdventOfCode2016 {
   internal static class Day7 {
      public static void Process() {

         var inputFile = File.ReadAllText(Path.Combine("Inputs", "Day7a.txt")).Replace("\r", "").Split('\n');

         var tlsTotal = 0;
         var sslTotal = 0;

         foreach (var input in inputFile) {
            if (SupportTLS(input)) {
               ++tlsTotal;
            } 
            if (SupportSSL(input)) {
               ++sslTotal;
            }
         }

         Console.WriteLine("Total TLS = " + tlsTotal);
         Console.WriteLine("Total SSL = " + sslTotal);

      }

      private static bool SupportSSL(string input) {
         var aba = new HashSet<string>();
         var bab = new HashSet<string>();

         var isHypernet = false;

         for (var index = 0; index < input.Length - 2; ++index) {
            isHypernet = (input[index].Equals('[')) || (!input[index].Equals(']')) && isHypernet;

            if ((!input[index].Equals(input[index + 2]) ||
                 (input[index].Equals(input[index + 1]) || (input[index + 1].Equals('[') || input[index + 1].Equals(']')))))
               continue;

            if (isHypernet) {
               bab.Add((input[index].ToString() + input[index + 1].ToString() + input[index + 2].ToString()));

            }
            else {
               aba.Add((input[index].ToString() + input[index + 1].ToString() + input[index + 2].ToString()));
            }
         }

         return aba.Any(key => bab.Contains(key[1].ToString() + key[0].ToString() + key[1].ToString()));
      }

      private static bool SupportTLS(string input) {
         var isAbba = false;
         var isHypernet = false;
         
         for (var index = 0; index < input.Length - 3; ++index) {
            isHypernet = (input[index].Equals('[')) || (!input[index].Equals(']')) && isHypernet;

            if ((!input[index].Equals(input[index + 3]) || !input[index + 1].Equals(input[index + 2])) ||
                (input[index].Equals(input[index + 1]) || input[index + 2].Equals(input[index + 3])))
               continue;

            if (isHypernet) {
               break;
            }
            else {
               isAbba = true;
            }
         }

         return (isAbba && !isHypernet);
      }
   }
}

/*
--- Day 7: Internet Protocol Version 7 ---

While snooping around the local network of EBHQ, you compile a list of IP addresses(they're IPv7, of course; IPv6 is much too limited). You'd like to figure out which IPs support TLS (transport-layer snooping).

An IP supports TLS if it has an Autonomous Bridge Bypass Annotation, or ABBA.An ABBA is any four-character sequence which consists of a pair of two different characters followed by the reverse of that pair, such as xyyx or abba.However, the IP also must not have an ABBA within any hypernet sequences, which are contained by square brackets.

For example:

abba[mnop] qrst supports TLS (abba outside square brackets).
abcd[bddb] xyyx does not support TLS(bddb is within square brackets, even though xyyx is outside square brackets).
aaaa[qwer] tyui does not support TLS(aaaa is invalid; the interior characters must be different).
ioxxoj[asdfgh] zxcvbn supports TLS(oxxo is outside square brackets, even though it's within a larger string).
How many IPs in your puzzle input support TLS?

 Your puzzle answer was 105.

--- Part Two ---


 You would also like to know which IPs support SSL (super-secret listening).

An IP supports SSL if it has an Area-Broadcast Accessor, or ABA, anywhere in the supernet sequences(outside any square bracketed sections), and a corresponding Byte Allocation Block, or BAB, anywhere in the hypernet sequences.An ABA is any three-character sequence which consists of the same character twice with a different character between them, such as xyx or aba.A corresponding BAB is the same characters but in reversed positions: yxy and bab, respectively.

For example:

aba[bab] xyz supports SSL(aba outside square brackets with corresponding bab within square brackets).
xyx[xyx] xyx does not support SSL(xyx, but no corresponding yxy).
aaa[kek] eke supports SSL(eke in supernet with corresponding kek in hypernet; the aaa sequence is not related, because the interior character must be different).
zazbz[bzb] cdb supports SSL(zaz has no corresponding aza, but zbz has a corresponding bzb, even though zaz and zbz overlap).
How many IPs in your puzzle input support SSL?

Your puzzle answer was 258.
*/
