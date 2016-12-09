/*
 * Advent of Code 2016
 * Day 8 (part 1 and 2)
 */
using System;
using System.IO;

namespace adventofcode
{
    class bscott08
    {
        private int _width, _height;
        private byte[] _screenData;

        public bscott08(int width, int height)
        {
            _width = width;
            _height = height;
            _screenData = new byte[width * height];
            Clear();
        }

        public void Clear()
        {
            // clear the screen
            for (int i = 0; i < _screenData.Length; i++)
                _screenData[i] = (byte)'.';
        }

        public void ProcessInstruction(string instruction)
        {
            string[] args = instruction.Split(new char[] { ' ' });
            int width = 0, height = 0, x = 0, y = 0, count = 0;
            switch (args[0])
            {
                case "rect":
                    string[] dimensions = args[1].Split(new char[] { 'x' });
                    int.TryParse(dimensions[0], out width);
                    int.TryParse(dimensions[1], out height);
                    Rect(width, height);
                    break;

                case "rotate":
                    if (args[1] == "column")
                    {
                        int.TryParse(args[2].Substring(2), out x);
                        int.TryParse(args[4], out count);
                        RotateColumn(x, count);
                    }
                    else
                    {
                        int.TryParse(args[2].Substring(2), out y);
                        int.TryParse(args[4], out count);
                        RotateRow(y, count);
                    }
                    break;
            }
        }

        private byte GetPixel(int y, int x)
        {
            return _screenData[(y * _width) + x];
        }

        private void SetPixel(int y, int x, byte value)
        {
            _screenData[(y * _width) + x] = value;
        }

        private void Rect(int width, int height)
        {
            for (int y = 0; y < height; y++)
                for (int x = 0; x < width; x++)
                    SetPixel(y, x, (byte)'#');
        }

        private void RotateColumn(int x, int count)
        {
            byte[] tempColumn = new byte[_height];
            // minipulate temp column
            for (int y = 0; y < _height; y++)
                tempColumn[(y + count) % _height] = GetPixel(y, x);

            for (int y = 0; y < _height; y++)
                SetPixel(y, x, tempColumn[y]);
        }

        private void RotateRow(int y, int count)
        {
            byte[] tempRow = new byte[_width];

            // minipulate temp row
            for (int x = 0; x < _width; x++)
                tempRow[(x + count) % _width] = GetPixel(y, x);

            for (int x = 0; x < _width; x++)
                SetPixel(y, x, tempRow[x]);
        }

        public int GetLitPixels()
        {
            int result = 0;
            for (int i = 0; i < _screenData.Length; i++)
                if (_screenData[i] != (byte)'.')
                    result++;
            return result;
        }

        public void DumpScreen()
        {
            for (int y = 0; y < _height; y++)
            {
                for (int x = 0; x < _width; x++)
                {
                    Console.Write((char)GetPixel(y, x));
                }
                Console.Write("\n");
            }
            Console.Write("\n");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            bscott08 day08 = new bscott08(50, 6);

            string[] input = File.ReadAllLines("input_day08.txt");

            for (int i = 0; i < input.Length; i++)
                day08.ProcessInstruction(input[i]);

            // Part 1 ( don't skim over the instructions >_< )
            Console.WriteLine("Pixels Lit: {0}\n", day08.GetLitPixels());

            // Part 2
            Console.WriteLine("Screen Dump: ");
            day08.DumpScreen();

            Console.ReadLine();
        }
    }
}
