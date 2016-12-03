/*
 * Advent of Code 2016
 * Day 2 (part 1)
 *
 * Command: clang++ --std=c++14 day02a.cpp
 *
 */

#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

typedef int keypad_t;
const keypad_t N = 0;
const int MAX_LINE_LENGTH = 2000;

int main(void) {
	// Open the input file
	std::ifstream fin("input02.txt");
	if (!fin) {
		std::cerr << "Error reading input file input02.txt" << std::endl;
		return -1;
	}

	// Build the keypad
	keypad_t keypad[5][5] =
	{
		{ N, N, N, N, N },
		{ N, 1, 2, 3, N },
		{ N, 4, 5, 6, N },
		{ N, 7, 8, 9, N },
		{ N, N, N, N, N }
	};

	// Read the input
	std::vector<std::string> input;
	char cInput[MAX_LINE_LENGTH];
	while (fin.getline(cInput, MAX_LINE_LENGTH)) {
		input.push_back(std::string(cInput));
	}
	fin.close();

	// Solve the problem
	std::vector<keypad_t> code;

	for (auto line : input) {
		int x = 2, y = 2;

		for (auto direction : line) {
			switch (direction) {
				case 'L':
					if (keypad[x][y - 1] != N) {
						y--;
					}

					break;
				case 'R':
					if (keypad[x][y + 1] != N) {
						y++;
					}

					break;
				case 'U':
					if (keypad[x - 1][y] != N) {
						x--;
					}

					break;
				case 'D':
					if (keypad[x + 1][y] != N) {
						x++;
					}

					break;
			}
		}

		code.push_back(keypad[x][y]);
	}

	for (auto digit : code) {
		std::cout << digit;
	}
	std::cout << std::endl;

	return 0;
}

