/*
 * Advent of Code 2016
 * Day 22 (part 1)
 *
 * Command: clang++ -std=c++14 rnelson22a.cpp
 *
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

using namespace std;

const string INPUT_FILE = "input22.txt";
const int MAX_LINE_LENGTH = 2000;
const regex PATTERN("/dev/grid/(node-x(\\d+)-y(\\d+))\\s+(\\d+)T\\s+(\\d+)T\\s+(\\d+)T\\s+(\\d+)%");

struct Node {
	string deviceName;
	string nodeName;
	int x;
	int y;
	int size;
	int used;
	int available;
	int usage;
};

Node parseLine(string input) {
	Node n;
	smatch matches;
	regex_match(input, matches, PATTERN);

	if (matches.size() == 8) {
		n.deviceName = "/dev/grid/" + string(matches[1]);
		n.nodeName = string(matches[1]);
		n.x = stoi(matches[2]);
		n.y = stoi(matches[3]);
		n.size = stoi(matches[4]);
		n.used = stoi(matches[5]);
		n.available = stoi(matches[6]);
		n.usage = stoi(matches[7]);
	} else {
		cout << "Error matching. Found " << matches.size() << " matches for " << input << endl;
	}

	return n;
}

bool isViable(Node a, Node b) {
	bool viable = true;

	if (a.used == 0) {
		viable = false;
	}

	if (a.x == b.x && a.y == b.y) {
		viable = false;
	}

	if (a.used > b.available) {
		viable = false;
	}

	return viable;
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

	// Remove the first two lines
	input.erase(begin(input), begin(input) + 2);

	// Solve the problem
	vector<Node> nodeList;
	for (auto line : input) {
		nodeList.push_back(parseLine(line));
	}

	auto viablePairs = 0;
	for (auto &nodeA : nodeList) {
		for (auto &nodeB : nodeList) {
			if (isViable(nodeA, nodeB)) {
				viablePairs++;
			}
		}
	}

	cout << "There are " << viablePairs << " viable pairs." << endl;

	return 0;
}

