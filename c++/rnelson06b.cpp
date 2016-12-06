/*
 * Advent of Code 2016
 * Day 6 (part 2)
 *
 * Command: clang++ --std=c++14 rnelson06b.cpp
 *
 */

#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const string INPUT_FILE = "input06.txt";
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
	auto length = input.at(0).length();
	vector<unordered_map<char, int>> counts;

	for (int i = 0; i < length; i++) {
		unordered_map<char, int> columnCounts;

		for (auto row : input) {
			char ch = row.at(i);
			auto location = columnCounts.find(ch);

			if (location == columnCounts.end()) {
				columnCounts.emplace(ch, 1);
			} else {
				int count = location->second;
				count++;

				columnCounts.erase(ch);
				columnCounts.emplace(ch, count);
			}
		}

		counts.push_back(columnCounts);
	}

	string message;
	for (auto column : counts) {
		auto min = numeric_limits<int>::max();
		auto ch = '\0';

		for (auto &pair : column) {
			if (pair.second < min) {
				min = pair.second;
				ch = pair.first;
			}
		}

		message += ch;
	}

	cout << "Message: \"" << message << "\"" << endl;

	return 0;
}

