/*
 * Advent of Code 2016
 * Day 14 (part 2)
 *
 * Command: clang++ --std=c++14 -lcrypto -I/usr/local/include -L/usr/local/lib rnelson14b.cpp
 *
 */

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <openssl/md5.h>

using namespace std;

const string INPUT_FILE = "input14.txt";
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

string _MD5(string input) {
	unsigned char digest[MD5_DIGEST_LENGTH];
	const char *inputCString = input.c_str();
	char md5String[33];

	MD5((unsigned char *)inputCString, strlen(inputCString), (unsigned char *)&digest);

	for (int i = 0; i < 16; i++) {
		sprintf(&md5String[i * 2], "%02x", (unsigned int)digest[i]);
	}

	return string(md5String);
}

string MD5(string input, int iterations) {
	// Hash the initial string
	string hash = _MD5(input);

	// Do any additional hashes
	for (auto i = 1; i < iterations; i++) {
		hash = _MD5(hash);
	}

	return hash;
}

string MD5(string input) {
	return MD5(input, 1);
}

char findTriplet(string input) {
	auto result = '\0';

	if (!input.size()) {
		return result;
	}

	for (auto i = 0; i < input.size() - 2; i++) {
		auto one = input.at(i);
		auto two = input.at(i + 1);
		auto three = input.at(i + 2);

		if (one == two && two == three) {
			result = one;
			break;
		}
	}

	return result;
}

map<int, string> generateHashes(string salt) {
	map<int, string> hashes;

	for (auto i = 0; i < 50000; i++) {
		auto hash = MD5(salt + to_string(i), 2017);
		if (findTriplet(hash) != '\0') {
			hashes[i] = hash;
		}
	}

	return hashes;
}

bool containsRepeatedCharacter(string input, char character, int number) {
	auto result = false;

	if (!input.size()) {
		return result;
	}

	for (auto i = 0; i < input.size() - number; i++) {
		if (input.at(i) == character) {
			result = true;
			
			for (auto j = i + 1; j < i + number; j++) {
				if (input.at(j) != character) {
					result = false;
					break;
				}
			}
		}

		if (result) {
			break;
		}
	}

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
	string input;
	fin >> input;
	fin.close();

	// Generate a bunch of hashes
	auto hashes = generateHashes(input);

	// Solve the problem
	int index = 0;
	auto keyCount = 0;
	vector<unsigned long long> otpIndexes;

	while (keyCount < 64) {
		auto triplet = findTriplet(hashes[index]);
		if (triplet != '\0') {
			for (auto i = index + 1; i < index + 1001; i++) {
				if (containsRepeatedCharacter(hashes[i], triplet, 5)) {
					otpIndexes.push_back(index);
					keyCount++;
					break;
				}
			}
		}

		index++;
	}

	cout << "The 64th key was found at index " << --index << "." << endl;

	return 0;
}

