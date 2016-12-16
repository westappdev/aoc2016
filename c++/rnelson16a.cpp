/*
 * Advent of Code 2016
 * Day 16 (part 1)
 *
 * Command: clang++ --std=c++14 rnelson16a.cpp
 *
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string INPUT_FILE = "input16.txt";
const int MAX_LINE_LENGTH = 2000;
const int SIZE = 272;

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

string generateData(string input, size_t length) {
	auto a = input;

	while (a.length() < length) {
		auto b = a;
		reverse(b.begin(), b.end());
		replace(b.begin(), b.end(), '0', 'x');
		replace(b.begin(), b.end(), '1', '0');
		replace(b.begin(), b.end(), 'x', '1');

		a = a + "0" + b;
	}

	return a.substr(0, length);
}

string generateChecksum(string input) {
	string checksum;

	for (auto i = 0; i < input.length() - 1; i += 2) {
		char one = input.at(i);
		char two = input.at(i + 1);

		if (one == two) {
			checksum += "1";
		} else {
			checksum += "0";
		}
	}

	return checksum;
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
	auto data = generateData(input, SIZE);
	auto sum = generateChecksum(data);

	while (sum.length() % 2 == 0) {
		sum = generateChecksum(sum);
	}

	cout << "Checksum: " << sum << endl;

	return 0;
}

