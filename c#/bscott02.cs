/*
 * Advent of Code 2016
 * Day 2 (part 1 and 2)
 */
using System;
using System.Text;

namespace adventofcode
{
    enum KeypadType
    {
        Exercise01,
        Exercise02
    }

    class bscott02
    {
        private int x = 1, y = 1;
        protected void ResetA()
        {
            this.x = 1;
            this.y = 1;
        }

        protected void ResetB()
        {
            this.x = 0;
            this.y = 2;
        }

        public string GetCode(string[] input, KeypadType keypadType)
        {
            StringBuilder outputBuffer = new StringBuilder();

            if (keypadType == KeypadType.Exercise01)
                ResetA();
            else
                ResetB();

            for (int i = 0; i < input.Length; i++)
            {
                if (keypadType == KeypadType.Exercise01)
                    outputBuffer.Append(GetDigitA(input[i]));
                else
                    outputBuffer.Append(GetDigitB(input[i]));
            }

            return outputBuffer.ToString();
        }

        protected string GetDigitA(string input)
        {
            for (int i = 0; i < input.Length; i++)
            {
                switch(input[i])
                {
                    case 'U':
                        if (y - 1 > -1) y--;
                        break;
                    case 'D':
                        if (y + 1 < 3) y++;
                        break;
                    case 'L':
                        if (x - 1 > -1) x--;
                        break;
                    case 'R':
                        if (x + 1 < 3) x++;
                        break;
                }
            }
            return (((y * 3) + x) + 1).ToString();
        }

        protected string GetDigitB(string input)
        {
            int[][] map = new int[][]
            {
                new int[] { 0,  0,  1,  0, 0 },
                new int[] { 0,  2,  3,  4, 0 },
                new int[] { 5,  6,  7,  8, 9 },
                new int[] { 0, 10, 11, 12, 0 },
                new int[] { 0,  0, 13,  0, 0 }
            };

            for (int i = 0; i < input.Length; i++)
            {
                switch (input[i])
                {
                    case 'U':
                        if (y - 1 > -1 && map[y - 1][x] != 0) y--;
                        break;
                    case 'D':
                        if (y + 1 < 5 && map[y + 1][x] != 0) y++;
                        break;
                    case 'L':
                        if (x - 1 > -1 && map[y][x - 1] != 0) x--;
                        break;
                    case 'R':
                        if (x + 1 < 5 && map[y][x + 1] != 0) x++;
                        break;
                }
            }
            return String.Format("{0:X}", map[y][x]);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            bscott02 exercise2 = new bscott02();

            string[] data = new string[]
            {
                "UUURRRRULRDLRDRRDURDDDLLDLLLULDUDDLDLULUURULRLDLRRLLLRRDRRLDDLLULUDUDDLRDRDUURDLURUURLRULLDDURULRRURDUURLULUUUURDDDDUUDLULRULLLRLLRRRURDLLRLLRRRUURULRDRUUDDDDDLLLRURRURRUURDUURDDRDLULRRLLLDRRRLURRLLURLDRRDDLDLRRLLRDRLLLLDLULDLRRDRRLDDURLULLUDLUDRRDRRLRLULURDRLRLUUUDLRLDLLLURDUDULULDDRUUURLLLDLLDDUDDRURURUDDLUULRDRRRRLDRDDURLUDURDULLDLUDLULDRLRLLRLLLLRURDURLLDRRDRLRUUUUULLLRUDURUDLLLUDLLLLRDLDRDUDRURLUDDUDDURLUUUUDDLLUDLULLLLLDUDLLRLRRDDDULULRLDRLLULDLUDLLURULRDDUURULRDLDLDLRL",
                "URUUURDULUDLUUUUDDRRRDRRRLDUDLRDRRDRDDLRUULDLLDUDULLLRLDRDRRLDLDLUUDRUULDUDULDUDURURDDURULDLURULRLULDUDDUULDLLLDDURDDRDDURUULUUDRLDDULDRRRRDURRUDLLLURDDDLRULLRDDRDDDDLUUDRDUULRRRRURULDDDLDDRDRRUDRRURUDRDDLDRRRLLURURUULUUDRDULLDRLRDRRDDURDUDLDRLUDRURDURURULDUUURDUULRRRRRUDLLULDDDRLULDDULUDRRRDDRUDRRDLDLRUULLLLRRDRRLUDRUULRDUDRDRRRDDRLLRUUDRLLLUDUDLULUUDULDRRRRDDRURULDULLURDLLLDUUDLLUDRLDURRRLDDDURUDUDURRULDD",
                "LRUDDULLLULRLUDUDUDRLLUUUULLUDLUUUUDULLUURDLLRDUDLRUDRUDDURURRURUDLLLRLDLUDRRRRRRDLUURLRDDDULRRUDRULRDRDDUULRDDLDULDRRRDDLURRURLLLRURDULLRUUUDDUDUURLRLDDUURLRDRRLURLDRLLUUURDRUUDUUUDRLURUUUDLDRRLRLLRRUURULLLRLLDLLLDULDDLDULDLDDRUDURDDURDUDURDLLLRRDDLULLLUDURLUDDLDLUUDRDRUDUUDLLDDLLLLDRDULRDLDULLRUDDUULDUDLDDDRUURLDRRLURRDDRUUDRUDLLDLULLULUDUDURDDRLRDLRLDRLDDRULLLRUDULDRLRLRULLRLLRRRLLRRRDDRULRUURRLLLRULDLUDRRDDLLLUDDUDDDLURLUDRDLURUUDLLDLULURRLLDURUDDDDRLULRDDLRLDDLRLLDDRRLRDUDUUULRRLRULUDURDUDRLRLRUDUDLLRRRRLRRUDUL",
                "RULLLLUUUDLLDLLRULLRURRULDDRDLUULDRLLRUDLLRRLRDURLLDUUUUURUUURDLUURRLDDDLRRRRLRULDUDDLURDRRUUDLRRRDLDDUDUDDRUDURURLDULLDLULDLLUDLULRDRLLURRLLDURLDLRDLULUDDULDLDDDDDUURRDRURLDLDULLURDLLDDLLUDLDLDRLRLDLRDRLDLRRUUDRURLUUUDLURUULDUDRDULLDURUDLUUURRRLLDUDUDDUUULLLRUULDLURUDDRLUDRDDLDLLUDUDRRRDDUUULUULLLRLLUURDUUDRUUULULLDLDRUUDURLLUULRLDLUURLLUUDRURDDRLURULDUDUUDRRUUURDULRLDUUDDRURURDRRULDDDRLUDLLUUDURRRLDLRLRDRURLURLLLRLDDLRRLDLDDURDUUDRDRRLDRLULDRLURUUUDDRLLLDDLDURLLLLDRDLDRRUDULURRLULRDRLLUULLRLRDRLLULUURRUDRUDDDLLDURURLURRRDLLDRDLUDRULULULRLDLRRRUUDLULDURLRDRLULRUUURRDDLRUURUDRURUDURURDD",
                "DURRDLLLDDLLDLLRLULULLRDLDRRDDRDLRULURRDUUDDRLLDDLDRRLRDUDRULDLRURDUUDRDDLLDRRDRUDUDULLDDDDLDRRRLRLRDRDLURRDDLDDDUUDRDRLLLDLUDDDLUULRDRLLLRLLUULUDDDRLDUUUURULRDDURRDRLUURLUDRLRLLLDDLRDDUULRRRRURDLDDDRLDLDRRLLDRDDUDDUURDLDUUDRDLDLDDULULUDDLRDDRLRLDDLUDLLDRLUDUDDRULLRLDLLRULRUURDDRDRDRURDRRLRDLLUDDRRDRRLDDULLLDLUDRRUDLDULDRURRDURLURRLDLRDLRUDLULUDDRULRLLDUURULURULURRLURRUULRULRRRLRDLULRLRLUDURDDRUUURDRLLRRRDDLDRRRULLDLRDRULDRRLRRDLUDDRDDDUUURRLULLDRRUULULLRRRRLDDRDDLUURLLUDLLDUDLULUULUDLLUUURRRUDDDRLLLRDRUUDUUURDRULURRLRDLLUURLRDURULDRRUDURRDDLDRLDRUUDRLLUDLRRU"
            };

            Console.WriteLine("Exercise 02 - Part 1: {0}", exercise2.GetCode(data, KeypadType.Exercise01));
            Console.WriteLine("Exercise 02 - Part 2: {0}", exercise2.GetCode(data, KeypadType.Exercise02));
            Console.ReadLine();
        }
    }
}
