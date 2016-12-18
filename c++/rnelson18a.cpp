/*
 * Advent of Code 2016
 * Day 18 (part 1)
 *
 * Command: clang++ --std=c++14 rnelson18a.cpp
 *
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string INPUT_FILE = "input18.txt";
const int MAX_LINE_LENGTH = 2000;
const int MAX_ROWS = 40;

bool isTrap(string row, size_t pos) {
	auto left = '.';
	auto center = row.at(pos);
	auto right = '.';

	if (pos != 0) {
		left = row.at(pos - 1);
	}
	if (pos != row.length() - 1) {
		right = row.at(pos + 1);
	}

	auto trap = false;

	if (left == '^' && center == '^' && right == '.') {
		trap = true;
	} else if (center == '^' && right == '^' && left == '.') {
		trap = true;
	} else if (left == '^' && center == '.' && right == '.') {
		trap = true;
	} else if (right == '^' && left == '.' && center == '.') {
		trap = true;
	}

	return trap;
}

string buildNextRow(string row) {
	string newRow;

	for (auto i = 0; i < row.length(); i++) {
		if (isTrap(row, i)) {
			newRow += "^";
		} else {
			newRow += ".";
		}
	}

	return newRow;
}

int main(void) {
	// Open the input file
	ifstream fin(INPUT_FILE);
	if (!fin) {
		cerr << "Error reading input file " << INPUT_FILE << endl;
		return -1;
	}

	// Read the input
	string input;
	fin >> input;
	fin.close();

	// Solve the problem
	vector<string> rows;
	int tiles = input.length();

	rows.push_back(input);
	string previousRow = input;

	auto safeTiles = count(input.begin(), input.end(), '.');
	auto rowCount = 1;
	while (rowCount < MAX_ROWS) {
		rowCount++;
		string nextRow = buildNextRow(previousRow);
		previousRow = nextRow;
		rows.push_back(nextRow);

		safeTiles += count(nextRow.begin(), nextRow.end(), '.');
	}

	for (auto row : rows) {
		cout << row << endl;
	}
	cout << endl << endl;

	cout << "There are " << safeTiles << " safe tiles." << endl;

	return 0;
}

