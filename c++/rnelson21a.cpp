/*
 * Advent of Code 2016
 * Day 21 (part 1)
 *
 * Command: clang++ -std=c++14 rnelson21a.cpp
 *
 */

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string INPUT_FILE = "input21.txt";
const int MAX_LINE_LENGTH = 2000;
const string START_TEXT = "abcdefgh";

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

string _swap(string input, int posX, int posY) {
	auto result = input;
	result[posX] = input[posY];
	result[posY] = input[posX];

	return result;
}

string _rotate(string input, int steps) {
	auto result = input;

	for (auto i = 0; i < abs(steps); i++) {
		if (steps < 0) {
			rotate(begin(result), begin(result) + 1, end(result));
		} else {
			rotate(rbegin(result), rbegin(result) + 1, rend(result));
		}
	}

	return result;
}

string _reverse(string input, int posX, int posY) {
	auto result = input;
	reverse(begin(result) + posX, begin(result) + posY + 1);
	return result;
}

string _move(string input, int posX, int posY) {
	auto result = input;
	auto temp = string(1, input.at(posX));

	result.erase(posX, 1);
	result.insert(posY, temp);

	return result;
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
	auto answer = START_TEXT;
	for (auto line : input) {
		auto bits = split(line, ' ');

		if (bits[0] == "swap") {
			auto posX = 0;
			auto posY = 0;

			if (bits[1] == "position") {
				posX = stoi(bits[2]);
				posY = stoi(bits[5]);
			} else {
				posX = answer.find_first_of(bits[2][0]);
				posY = answer.find_first_of(bits[5][0]);
			}

			answer = _swap(answer, posX, posY);
		} else if (bits[0] == "rotate") {
			if (bits[1] == "based") {
				auto letterX = bits[6];
				auto pos = answer.find_first_of(letterX);
				auto steps = 1 + pos + (pos >= 4 ? 1 : 0);

				answer = _rotate(answer, steps);
			} else {
				auto steps = stoi(bits[2]);

				if (bits[1] == "left") {
					steps *= -1;
				}

				answer = _rotate(answer, steps);
			}
		} else if (bits[0] == "reverse") {
			auto posX = stoi(bits[2]);
			auto posY = stoi(bits[4]);

			answer = _reverse(answer, posX, posY);
		} else if (bits[0] == "move") {
			auto posX = stoi(bits[2]);
			auto posY = stoi(bits[5]);

			answer = _move(answer, posX, posY);
		} else {
			cerr << "error: cannot understand instruction \"" << line << "\"" << endl;
			return 1;
		}
	}

	cout << "Password: " << answer << endl;

	return 0;
}

