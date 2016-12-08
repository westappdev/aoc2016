/*
 * Advent of Code 2016
 * Day 7 (part 1)
 *
 * Command: clang++ --std=c++14 rnelson07a.cpp
 *
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string INPUT_FILE = "input07.txt";
const int MAX_LINE_LENGTH = 2000;

int main(void) {
	// Open the input file
	ifstream fin(INPUT_FILE);
	if (!fin) {
		cerr << "Error reading input file " << INPUT_FILE << endl;
		return -1;
	}
 
	// Read the input
	vector<string> input;
	char cInput[MAX_LINE_LENGTH];
	while (fin.getline(cInput, MAX_LINE_LENGTH)) {
		input.push_back(string(cInput));
	}
	fin.close();

	// Solve the problem
	int count = 0;

	for (auto line : input) {
		int end = line.length() - 3;
		bool inside = false;
		bool abba = false;

		for (int i = 0; i < end; i++) {
			// Check to see if we've entered/ended a hypernet sequence
			if (line.at(i) == '[') {
				inside = true;
				continue;
			} else if (line.at(i) == ']') {
				inside = false;
				continue;
			}

			// Look for an ABBA
			if (line.at(i) == line.at(i + 3)) {
				if (line.at(i + 1) == line.at(i + 2)) {
					if (line.at(i) != line.at(i + 1)) {
						abba = true;

						if (inside) {
							break;
						}
					}
				}
			}
		}

		if (abba && !inside) {
			count++;
		}
	}

	cout << "Count: " << count << endl;

	return 0;
}

