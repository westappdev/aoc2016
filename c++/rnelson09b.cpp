/*
 * Advent of Code 2016
 * Day 9 (part 1)
 *
 * Command: clang++ --std=c++14 rnelson09a.cpp
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string INPUT_FILE = "input09.txt";
const int MAX_LINE_LENGTH = 2000;

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
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
	string input;
	fin >> input;
	fin.close();

	// Solve the problem
	string decompressed = input;
	size_t leftmost = 0;
	size_t open = decompressed.find("(", leftmost);
	size_t close = decompressed.find(")", leftmost);

	while (open != string::npos && close != string::npos && open != decompressed.length()) {
		string left = decompressed.substr(0, open);
		string instruction = decompressed.substr(open + 1, close - open - 1);
		string right = decompressed.substr(close + 1);

		string newDecompressed = left;

		vector<string> instrBits = split(instruction, 'x');
		int characters = stoi(instrBits.at(0));
		int count = stoi(instrBits.at(1));

		string repeated = right.substr(0, characters);
		string untouched = right.substr(characters);

		for (int i = 0; i < count; i++) {
			newDecompressed += repeated;
		}

		leftmost = newDecompressed.size();
		newDecompressed += untouched;
		decompressed = newDecompressed;

		open = decompressed.find("(", leftmost);
		close = decompressed.find(")", leftmost);
	}

	cout << "Length: " << decompressed.length() << endl;

	return 0;
}

