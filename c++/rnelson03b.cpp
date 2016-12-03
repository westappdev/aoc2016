/*
 * Advent of Code 2016
 * Day 3 (part 2)
 *
 * Command: clang++ --std=c++14 -I/usr/local/include -L/usr/local/lib rnelson03b.cpp
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
	std::vector<std::string> partsA, partsB, partsC;
	int parts = 0;
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

		partsA.push_back(bits.at(0));
		partsB.push_back(bits.at(1));
		partsC.push_back(bits.at(2));
		parts++;

		if (parts == 3) {
			Triangle t1(partsA.at(0), partsA.at(1), partsA.at(2));
			Triangle t2(partsB.at(0), partsB.at(1), partsB.at(2));
			Triangle t3(partsC.at(0), partsC.at(1), partsC.at(2));

			partsA.clear();
			partsB.clear();
			partsC.clear();

			candidates.push_back(t1);
			candidates.push_back(t2);
			candidates.push_back(t3);
			parts = 0;
		}
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

