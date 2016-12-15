/*
 * Advent of Code 2016
 * Day 15 (part 2)
 *
 * Command: clang++ --std=c++14 rnelson15b.cpp
 *
 */

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string INPUT_FILE = "input15.txt";
const int MAX_LINE_LENGTH = 2000;

void split(const string &s, char delim, vector<string> &elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

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
	vector<pair<int, int>> sculpture;

	// Parse the input
	auto number = 1;
	for (auto line : input) {
		auto bits = split(line, ' ');

		auto positions = stoi(bits[3]);
		auto initialPosition = stoi(bits[11].substr(0, bits[11].length() - 1));

		sculpture.push_back(make_pair(positions, initialPosition));

		number++;
	}

	// Add the new disc
	sculpture.push_back(make_pair(11, 0));

	auto time = 0;
	auto count = sculpture.size();
	auto got = false;

	while (!got) {
		auto result = true;

		for (auto i = 1; i <= count; i++) {
			auto pair = sculpture.at(i - 1);
			auto positions = pair.first;
			auto initialPosition = pair.second;

			auto position = initialPosition + i + time;

			if ((position % positions) != 0) {
				result = false;
			}

		}

		got = result;
		if (!got) {
			time++;
		}
	}

	cout << "We got a disc by pressing the button at time " << time << "." << endl;

	return 0;
}

