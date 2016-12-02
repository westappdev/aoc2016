/*
 * Advent of Code 2016
 * Day 1 (part 2)
 *
 * Command: clang++ --std=c++14 rnelson01b.cpp
 * Sources:
 *		http://stackoverflow.com/a/236803 (split())
 *		http://stackoverflow.com/a/5891643 (removing spaces)
 *
 */

#include <cmath>
#include <cstdlib>
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

bool haveVisited(std::vector<std::string> vec, int x, int y) {
	std::string location = std::to_string(x) + "," + std::to_string(y);

	auto dup = std::find(vec.begin(), vec.end(), location);
	if (dup != vec.end()) {
		std::vector<std::string> magnitudes = split(*dup, ',');
		int spaces = 0;
		for (auto m : magnitudes) { spaces += abs(atoi(m.c_str())); }

		std::cout << "Found duplicate at " << *dup << ". Differs by " << spaces << " spaces." << std::endl;
		return true;
	} else {
		return false;
	}
}

void markVisited(std::vector<std::string> &vec, int x, int y) {
	if (haveVisited(vec, x, y)) {
		exit(0);
	}

	vec.push_back(std::to_string(x) + "," + std::to_string(y));
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

	// Build a vector to store where we've been
	std::vector<std::string> visited;

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
						for (uint diff = 0; diff < spaces; ++diff) {
							x -= 1;
							markVisited(visited, x, y);
						}
						facing = WEST;
						break;
					case SOUTH:
						for (uint diff = 0; diff < spaces; ++diff) {
							x += 1;
							markVisited(visited, x, y);
						}
						facing = EAST;
						break;
					case EAST:
						for (uint diff = 0; diff < spaces; ++diff) {
							y += 1;
							markVisited(visited, x, y);
						}
						facing = NORTH;
						break;
					case WEST:
						for (uint diff = 0; diff < spaces; ++diff) {
							y -= 1;
							markVisited(visited, x, y);
						}
						facing = SOUTH;
						break;
				}

				break;
			case 'R':
				switch (facing) {
					case NORTH:
						for (uint diff = 0; diff < spaces; ++diff) {
							x += 1;
							markVisited(visited, x, y);
						}
						facing = EAST;
						break;
					case SOUTH:
						for (uint diff = 0; diff < spaces; ++diff) {
							x -= 1;
							markVisited(visited, x, y);
						}
						facing = WEST;
						break;
					case EAST:
						for (uint diff = 0; diff < spaces; ++diff) {
							y -= 1;
							markVisited(visited, x, y);
						}
						facing = SOUTH;
						break;
					case WEST:
						for (uint diff = 0; diff < spaces; ++diff) {
							y += 1;
							markVisited(visited, x, y);
						}
						facing = NORTH;
						break;
				}

				break;
		}
	}

	return 1;
}
