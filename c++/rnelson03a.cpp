/*
 * Advent of Code 2016
 * Day 3 (part 1)
 *
 * Command: clang++ --std=c++14 -I/usr/local/include -L/usr/local/lib rnelson03a.cpp
 *
 */

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

const int MAX_LINE_LENGTH = 2000;

class Triangle {
	public:
		Triangle(int, int, int);
		Triangle(std::string, std::string, std::string);
		int a;
		int b;
		int c;
		bool valid();
};

Triangle::Triangle(int a, int b, int c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

Triangle::Triangle(std::string a, std::string b, std::string c) {
	this->a = atoi(a.c_str());
	this->b = atoi(b.c_str());
	this->c = atoi(c.c_str());
}

bool Triangle::valid() {
	return ((this->a + this->b > this->c) && (this->a + this->c > this->b) && (this->b + this->c > this->a));
}

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
	std::ifstream fin("input03.txt");
	if (!fin) {
		std::cerr << "Error reading input file input03.txt" << std::endl;
		return -1;
	}

	std::vector<Triangle> candidates;

	// Read the input
	std::vector<std::string> input;
	char cInput[MAX_LINE_LENGTH];
	while (fin.getline(cInput, MAX_LINE_LENGTH)) {
		using namespace std;
		using namespace boost;

		vector<string> bits;
		string input(cInput);
		tokenizer<> tokenizer(input);

		for (auto token : tokenizer) {
			bits.push_back(token);
		}

		Triangle t(bits.at(0), bits.at(1), bits.at(2));
		candidates.push_back(t);
	}
	fin.close();

	// Solve the problem
	int triangles = 0; int other = 0;
	for (auto t : candidates) {
		if (t.valid()) {
			triangles++;
		} else {
			other++;
		}
	}

	std::cout << "Triangles: " << triangles << std::endl << "Non-triangles: " << other << std::endl;

	return 0;
}

