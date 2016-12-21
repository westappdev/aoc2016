/*
 * Advent of Code 2016
 * Day 20 (part 2)
 *
 * Command: clang++ -std=c++14 rnelson20b.cpp
 *
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string INPUT_FILE = "input20.txt";
const int MAX_LINE_LENGTH = 2000;
const int MAX_IP = 4294967295;

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

auto max(long a, long b) -> long {
	if (a >= b) {
		return a;
	} else {
		return b;
	}
}

auto main(void) -> int {
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
	vector<pair<long, long>> ranges;
	auto allowed = 0L;
	auto currentLow = -1L;
	auto currentHigh = -1L;
	
	for (auto line : input) {
		auto bits = split(line, '-');
		long low = stol(bits[0]);
		long high = stol(bits[1]);

		ranges.push_back(make_pair(low, high));
	}

	sort(begin(ranges), end(ranges), [](auto &left, auto &right) -> bool {
		return left.first < right.first;
	});

	for (auto &pair : ranges) {
		auto low = pair.first;
		auto high = pair.second;

		if (currentLow == -1 && currentHigh == -1) {
			currentLow = low;
			currentHigh = high;

			allowed += max(0, currentLow - 1);
		} else {
			allowed += max(0, low - currentHigh - 1);
		}

		currentHigh = max(currentHigh, high);
	}
	allowed += max(0, MAX_IP - currentHigh);

	cout << allowed << " IPs are allowed by the blacklist." << endl;

	return 0;
}

