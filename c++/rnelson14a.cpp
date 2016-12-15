/*
 * Advent of Code 2016
 * Day 14 (part 1)
 *
 * Command: clang++ --std=c++14 -lcrypto -I/usr/local/include -L/usr/local/lib rnelson14a.cpp
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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

string MD5(string input) {
	unsigned char digest[MD5_DIGEST_LENGTH];
	const char *inputCString = input.c_str();
	char md5String[33];

	MD5((unsigned char *)inputCString, strlen(inputCString), (unsigned char *)&digest);

	for (int i = 0; i < 16; i++) {
		sprintf(&md5String[i * 2], "%02x", (unsigned int)digest[i]);
	}

	return string(md5String);
}

char findTriplet(string input) {
	auto result = '\0';

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

bool containsRepeatedCharacter(string input, char character, int number) {
	auto result = false;

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

	// Solve the problem
	vector<unsigned long long> otpIndexes;
	unsigned long long index = 0;

	while (otpIndexes.size() < 64) {
		string str = input + to_string(index);
		string hash = MD5(str);

		auto triplet = findTriplet(hash);

		if (triplet != '\0') {
			for (unsigned long long index2 = index + 1; index2 <= index + 1000; index2++) {
				string newStr = input + to_string(index2);
				string newHash = MD5(newStr);

				if (containsRepeatedCharacter(newHash, triplet, 5)) {
					otpIndexes.push_back(index);
					break;
				}
			}
		}
		
		index++;
	}

	cout << "The 64th one-time pad key was produced at index " << otpIndexes.at(63) << endl;

	return 0;
}

