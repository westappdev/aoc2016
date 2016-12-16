/*
 * Advent of Code 2016
 * Day 16 (part 2)
 *
 * Command: clang++ --std=c++14 rnelson16a.cpp
 *
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const string INPUT_FILE = "input16.txt";
const int SIZE = 35651584;

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

