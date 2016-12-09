/*
 * Advent of Code 2016
 * Day 8 (part 2)
 *
 * Command: clang++ --std=c++14 rnelson08b.cpp
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const string INPUT_FILE = "input08.txt";
const int MAX_LINE_LENGTH = 2000;
const int DISPLAY_WIDTH = 50;
const int DISPLAY_HEIGHT = 6;

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

string make_coordinate(int x, int y) {
	return to_string(y) + "," + to_string(x);
}

void printDisplay(unordered_map<string, bool> display) {
	for (int x = 0; x < DISPLAY_HEIGHT; x++) {
		for (int y = 0; y < DISPLAY_WIDTH; y++) {
			string coordinate = make_coordinate(x, y);
			bool on = display[coordinate];

			if (on) {
				cout << "#";
			} else {
				cout << ".";
			}
		}
		
		cout << endl;
	}
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
	unordered_map<string, bool> display;

	// Initialize the entire display to off
	for (int x = 0; x < DISPLAY_HEIGHT; x++) {
		for (int y = 0; y < DISPLAY_WIDTH; y++) {
			string coordinate = make_coordinate(x, y);
			display[coordinate] = false;
		}
	}

	for (auto line : input) {
		if ("rect " == line.substr(0, 5)) {
			vector<string> sizes = split(line.substr(5), 'x');
			int width = stoi(sizes.at(0));
			int height = stoi(sizes.at(1));

			for (int x = 0; x < height; x++) {
				for (int y = 0; y < width; y++) {
					string coordinate = make_coordinate(x, y);
					display[coordinate] = true;
				}
			}
		} else if ("rotate column " == line.substr(0, 14)) {
			int equals = line.find("=");
			string end = line.substr(equals + 1);
			vector<string> numbers = split(end, ' ');

			int column = stoi(numbers.at(0));
			int distance = stoi(numbers.at(2));

			for (int i = 0; i < distance; i++) {
				// Save the bottom value
				bool saved = display[make_coordinate(DISPLAY_HEIGHT - 1, column)];

				// Move everything else down
				for (int row = 0; row < DISPLAY_HEIGHT; row++) {
					string coord = make_coordinate(row, column);

					bool temporary = display[coord];
					display[coord] = saved;
					saved = temporary;
				}
			}
		} else if ("rotate row " == line.substr(0, 11)) {
			int equals = line.find("=");
			string end = line.substr(equals + 1);
			vector<string> numbers = split(end, ' ');

			int row = stoi(numbers.at(0));
			int distance = stoi(numbers.at(2));

			for (int i = 0; i < distance; i++) {
				// Save the rightmost value
				bool saved = display[make_coordinate(row, DISPLAY_WIDTH - 1)];

				// Move everything else right
				for (int column = 0; column < DISPLAY_WIDTH; column++) {
					string coord = make_coordinate(row, column);

					bool temporary = display[coord];
					display[coord] = saved;
					saved = temporary;
				}
			}
		}
	}

	printDisplay(display);
	return 0;
}

