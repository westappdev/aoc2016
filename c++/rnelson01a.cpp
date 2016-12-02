/*
 * Advent of Code 2016
 * Day 1 (part 1)
 *
 * Command: clang++ --std=c++14 rnelson01a.cpp
 * Sources:
 *		http://stackoverflow.com/a/236803 (split())
 *		http://stackoverflow.com/a/5891643 (removing spaces)
 *
 */

#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

enum facing_t { NORTH, SOUTH, EAST, WEST };

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

void removeChars(std::string &s, char *chars) {
	for (uint i = 0; i < strlen(chars); ++i) {
		s.erase(remove(s.begin(), s.end(), chars[i]), s.end());
	}
}

int main(void) {
	// Open the input file
	std::ifstream fin("day01a.in");
	if (!fin) {
		std::cerr << "Error reading input file day01a.in" << std::endl;
		return -1;
	}

	// Read the input
	char cInput[2000];
	fin.getline(cInput, 2000);
	fin.close();

	// Split the input into individual directions
	std::string input = std::string(cInput);
	input.erase(remove(input.begin(), input.end(), ' '), input.end());
	std::vector<std::string> directions = split(input, ',');

	// Solve the problem
	facing_t facing = NORTH;
	int x = 0;
	int y = 0;

	for (auto d : directions) {
		char direction = d.c_str()[0];
		const char *magnitude = d.substr(1).c_str();

		int spaces;
		std::stringstream(std::string(magnitude)) >> spaces;

		switch (direction) {
			case 'L':
				switch (facing) {
					case NORTH:
						x -= spaces;
						facing = WEST;
						break;
					case SOUTH:
						x += spaces;
						facing = EAST;
						break;
					case EAST:
						y += spaces;
						facing = NORTH;
						break;
					case WEST:
						y -= spaces;
						facing = SOUTH;
						break;
				}

				break;
			case 'R':
				switch (facing) {
					case NORTH:
						x += spaces;
						facing = EAST;
						break;
					case SOUTH:
						x -= spaces;
						facing = WEST;
						break;
					case EAST:
						y -= spaces;
						facing = SOUTH;
						break;
					case WEST:
						y += spaces;
						facing = NORTH;
						break;
				}

				break;
		}
	}

	int blocks = abs(x) + abs(y);
	std::cout << blocks << std::endl;

	return 0;
}
