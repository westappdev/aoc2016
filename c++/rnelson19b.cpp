/*
 * Advent of Code 2016
 * Day 19 (part 2)
 *
 * Command: clang++ --std=c++14 rnelson19b.cpp
 *
 */

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const string INPUT_FILE = "input19.txt";
const int MAX_LINE_LENGTH = 2000;

int main(void) {
	// Open the input file
	ifstream fin(INPUT_FILE);
	if (!fin) {
		cerr << "Error reading input file " << INPUT_FILE << endl;
		return -1;
	}

	// Read the input
	long input;
	string line;
	fin >> line;
	fin.close();
	input = stol(line);

	// Solve the problem
	deque<long> circle;
	for (auto i = 1; i <= input; i++) {
		circle.push_back(i);
	}

	while (circle.size() > 1) {
		auto thief = circle.at(0);
		unsigned int victim_idx = circle.size() / 2;

		// Remove the victim
		circle.erase(circle.begin() + victim_idx);

		// Rotate
		circle.push_back(circle.at(0));
		circle.pop_front();
	}

	cout << "The winning elf is " << circle.at(0) << "." << endl;

	return 0;
}

