/*
 * Advent of Code 2016
 * Day 20 (part 1)
 *
 * Command: clang++ -std=c++14 rnelson20a.cpp
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string INPUT_FILE = "input20.txt";
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
	vector<pair<unsigned long long, unsigned long>> ranges;

	for (auto line : input) {
		auto bits = split(line, '-');
		unsigned long long low = stoull(bits[0]);
		unsigned long long high = stoull(bits[1]);

		ranges.push_back(make_pair(low, high));
	}

	for (int i = 0; i < numeric_limits<int>::max(); i++) {
		bool allowed = true;

		for (auto &pair : ranges) {
			auto low = pair.first;
			auto high = pair.second;

			if (i >= low && i <= high) {
				allowed = false;
				break;
			}
		}

		if (allowed) {
			cout << "First allowed address is " << i << "." << endl;
			break;
		}
	}

	return 0;
}

