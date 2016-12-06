/*
 * Advent of Code 2016
 * Day 5 (part 1)
 *
 * Command: clang++ --std=c++14 -lcrypto rnelson05a.cpp
 *
 */

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <openssl/md5.h>

using namespace std;

const string INPUT_FILE = "input05.txt";
const int MAX_LINE_LENGTH = 2000;
typedef unsigned long long ull;

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
	string password = "";
	ull index = 0;

	while (password.length() != 8) {
		string input = doorId + to_string(index);
		string hash = MD5(input);

		//cout << "md5(" << input << ") = " << hash << "\t" << password << endl;

		if (hash.substr(0, 5) == "00000") {
			password += hash.at(5);
		}

		index++;
	}

	cout << "Password: " << password << endl;

	return 0;
}
