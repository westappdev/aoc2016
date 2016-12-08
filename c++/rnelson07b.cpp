/*
 * Advent of Code 2016
 * Day 7 (part 2)
 *
 * Command: clang++ --std=c++14 rnelson07b.cpp
 *
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
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
		set<string> aba;
		set<string> bab;

		int end = line.length() - 2;
		bool inside = false;

		for (int i = 0; i < end; i++) {
			char first = line.at(i);
			char second = line.at(i + 1);
			char third = line.at(i + 2);

			// Check to see if we've entered/ended a hypernet sequence
			if (first == '[') {
				inside = true;
				continue;
			} else if (first == ']') {
				inside = false;
				continue;
			}

			// If there's a bracket in the middle, move on
			if (second == '[' || second == ']') {
				continue;
			}

			// Look for ABAs/BABs
			if (first == third && first != second) {
				if (!inside) {
					string candidate = line.substr(i, 3);

					aba.emplace(candidate);
				} else {
					string candidate;
					candidate += second;
					candidate += first;
					candidate += second;

					bab.emplace(candidate);
				}
			}
		}

		// Check for a match
		bool add = false;
		for (auto a : aba) {

			for (auto b : bab) {
				if (a == b) {
					add = true;
					break;
				}
			}

		}

		if (add) {
			count++;
		}
	}

	cout << "Count: " << count << endl;

	return 0;
}

