/*
 * Advent of Code 2016
 * Day 12 (part 1)
 *
 * Command: clang++ --std=c++14 rnelson012a.cpp
 *
 */

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string INPUT_FILE = "input12.txt";
const int MAX_LINE_LENGTH = 2000;
const char START_REGISTER = 'a';
const char END_REGISTER = 'd';

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

enum opcode_t { CPY, INC, DEC, JNZ, UNKNOWN_OPCODE };

struct Command {
	opcode_t opcode;
	int operandCount;
	string operand1;
	string operand2;
};

Command parseInstruction(string line) {
	Command result;

	auto opcode = line.substr(0, 3);
	auto operands = split(line.substr(4), ' ');

	if (opcode == "cpy") {
		result.opcode = CPY;
	} else if (opcode == "inc") {
		result.opcode = INC;
	} else if (opcode == "dec") {
		result.opcode = DEC;
	} else if (opcode == "jnz") {
		result.opcode = JNZ;
	} else {
		result.opcode = UNKNOWN_OPCODE;
	}

	result.operandCount = operands.size();
	result.operand1 = operands.at(0);

	if (operands.size() > 1) {
		result.operand2 = operands.at(1);
	}

	return result;
}

void printRegisters(map<char, int> registers) {
	cout << "Registers" << endl << "---------" << endl;
	for (auto &pair : registers) {
		cout << "\t" << pair.first << ": " << pair.second << endl;
	}
}

void processMath(map<char, int> &registers, Command instruction) {
	auto value = registers[instruction.operand1[0]];
	auto oVal = value;
	
	switch (instruction.opcode) {
		case INC:
			value++;
			break;
		case DEC:
			value--;
			break;
		case CPY:
		case JNZ:
		case UNKNOWN_OPCODE:
			// don't do anything
			break;
	}

	registers[instruction.operand1[0]] = value;
}

void processCopy(map<char, int> &registers, Command instruction) {
	auto value = numeric_limits<int>::min();

	// Try to parse the response as a string
	if (istringstream(instruction.operand1) >> value) {
		// We had a number, good to go.
	} else {
		value = registers[instruction.operand1[0]];
	}

	registers[instruction.operand2[0]] = value;
}

int processJump(map<char, int> registers, Command instruction) {
	int offset = 0;

	auto value = 0;
	int requestedOffset = stoi(instruction.operand2);

	if (istringstream(instruction.operand1) >> value) {
		// We had a number, good to go.
	} else {
		value = registers[instruction.operand1[0]];
	}

	if (value != 0) {
		offset = requestedOffset;
	}

	return offset;
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

	map<char, int> registers;
	int sp = 0;

	// Prepopulate all registers with 0
	for (char reg = START_REGISTER; reg <= END_REGISTER; reg++) {
		registers[reg] = 0;
	}
	
	// Solve the problem
	while (sp < input.size()) {
		auto line = input.at(sp);
		auto instruction = parseInstruction(line);
		auto offset = 0;

		switch (instruction.opcode) {
			case CPY:
				processCopy(registers, instruction);
				sp++;
				break;

			case INC:
			case DEC:
				processMath(registers, instruction);
				sp++;
				break;

			case JNZ:
				offset = processJump(registers, instruction);
				
				if (offset == 0) {
					sp++;
				} else {
					sp += offset; // move by the offset amount
				}
				break;

			case UNKNOWN_OPCODE:
				cerr << "Unrecognized instruction: " << line << endl << "Terminating." << endl;
				return -1;
		}
	}

	printRegisters(registers);
	
	return 0;
}

