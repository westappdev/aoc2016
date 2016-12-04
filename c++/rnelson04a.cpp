/*
 * Advent of Code 2016
 * Day 4 (part 1)
 *
 * Command: clang++ --std=c++14 day04a.cpp
 *
 */

#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

const regex PATTERN("([A-Za-z-]+)([0-9]+)\\[([^\\]]+)\\]"); // ([A-Za-z-]+)([0-9]+)\[([^\]]+)\]
const int MAX_LINE_LENGTH = 2000;

class Room {
	public:
		string code;
		string letters;
		string number;
		string checksum;
		bool isValid();
};

bool Room::isValid() {
	bool result = false;

	// Count the occurrences of every letter
	unordered_map<char, int> counts;

	for (auto ch : this->letters) {
		const char *cstr = this->letters.c_str();
		int count = 0;

		for (size_t i = 0; i < strlen(cstr); i++) {
			if (cstr[i] == ch) {
				count++;
			}
		}

		counts.emplace(ch, count);
	}

	// Find the largest count
	int maxCount = -1;
	for (auto &pair : counts) {
		if (pair.second > maxCount) {
			maxCount = pair.second;
		}
	}

	// Build the checksum
	string checksum;
	for (int i = maxCount; i > -1; i--) {
		set<char> characters;

		// Get all characters that have this number of occurrences
		for (auto &pair : counts) {
			if (pair.second == i) {
				characters.insert(pair.first);
			}
		}

		for (auto ch : characters) {
			checksum += ch;
		}
	}

	if (this->checksum == checksum.substr(0, 5)) {
		result = true;
	}

	return result;
}

int main(void) {
	// Open the input file
	ifstream fin("input04.txt");
	if (!fin) {
		cerr << "Error reading input file input04.txt" << endl;
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
	vector<Room> rooms;
	vector<Room> validRooms;

	// Build some Room objects to work from, parsing the input rows
	for (auto code : input) {
		smatch matches;
		regex_match(code, matches, PATTERN);

		if (matches.size()) {
			Room r;
			r.code = code;
			r.letters = matches[1];
			r.number = matches[2];
			r.checksum = matches[3];

			// Remove hyphens from the pile of letters
			r.letters.erase(remove(r.letters.begin(), r.letters.end(), '-'), r.letters.end());

			rooms.push_back(r);
		}
	}
	
	// Save only the valid ones
	for (auto room : rooms) {
		if (room.isValid()) {
			validRooms.push_back(room);
		}
	}

	// Count the sector IDs
	int sum = 0;
	for (auto room : validRooms) {
		sum += atoi(room.number.c_str());
	}

	cout << "Sum of sector IDs: " << sum << endl;

	return 0;
}

