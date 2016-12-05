/*
 * Advent of Code 2016
 * Day 5 (part 2)
 *
 * Command: clang++ --std=c++14 rnelson05b.cpp
 *
 */

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include "rnelson-day05.h"

using namespace std;

const string INPUT_FILE = "input05.txt";
const int MAX_LINE_LENGTH = 2000;
typedef unsigned long long ull;

int main(void) {
	// Open the input file
	ifstream fin(INPUT_FILE);
	if (!fin) {
		cerr << "Error reading input file " << INPUT_FILE << endl;
		return -1;
	}

	// Read the input
	string doorId;
	fin >> doorId;
	fin.close();

	// Solve the problem
	string password = "________";
	ull index = 0;
	size_t firstUnderscore = 0;

	while (firstUnderscore != string::npos) {
		string input = doorId + to_string(index);
		string hash = MD5(input).hexdigest();

		if (hash.substr(0, 5) == "00000") {
			char location = hash.at(5);
			char ch = hash.at(6);
			bool validLocation = location >= '0' && location <= '7';

			if (validLocation) {
				int index = (char)(location - '0');

				if (password.at(index) == '_') {
					password.at(index) = ch;
				}

				//cout << "Current password: " << password << endl;
			}
		}

		index++;
		firstUnderscore = password.find("_");
	}

	cout << "Password: " << password << endl;

	return 0;
}
