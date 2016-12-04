/*
 * Advent of Code 2016
 * Day 4 (part 2)
 *
 * Command: clang++ --std=c++14 day04b.cpp
 * Sources:
 *		http://stackoverflow.com/a/217605/187404 (rtrim())
 *
 */

#include <algorithm>
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

static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

class Room {
	public:
		string code;
		string str;
		string letters;
		int number;
		string checksum;
		bool isValid();
		string decrypt();
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

string Room::decrypt() {
	string decrypted;

	for (auto ch : this->str) {
		if (ch == ' ') {
			decrypted += ch;
		} else {
			decrypted += (char)((((ch - 97) + this->number) % 26) + 97);
		}
	}

	return decrypted;
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

	// Build some Room objects to work from, parsing the input rows
	for (auto code : input) {
		smatch matches;
		regex_match(code, matches, PATTERN);

		if (matches.size()) {
			Room r;
			r.code = code;
			r.letters = matches[1];
			r.str = string(r.letters);
			r.number = atoi(string(matches[2]).c_str());
			r.checksum = matches[3];

			// Replace hyphens with spaces
			replace(r.str.begin(), r.str.end(), '-', ' ');
			rtrim(r.str);

			rooms.push_back(r);
		}
	}
	
	for (auto room : rooms) {
		string roomName = room.decrypt();

		// Find "north" and "pole" in the string
		size_t northPos = roomName.find("north");
		size_t polePos = roomName.find("pole");

		if (northPos != string::npos && polePos != string::npos) {
			cout << roomName << ", sector " << room.number << endl;
		}
	}

	return 0;
}

