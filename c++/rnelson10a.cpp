/*
* Advent of Code 2016
* Day 10 (part 1)
*
* Command: clang++ --std=c++14 rnelson10a.cpp
*
*/

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int CHIP_A = 61;
const int CHIP_B = 17;

const string INPUT_FILE = "input10.txt";
const int MAX_LINE_LENGTH = 2000;

enum magnitude_t { LOW, HIGH };
enum destination_t { OUTPUT, BOT };

struct Transfer {
	magnitude_t mag;
	destination_t dest;
	int destNumber;
};

class Bot {
public:
	Bot();
	Bot(int number);
	void addChip(int value);
	int getChip(magnitude_t mag);
	bool isFull();
private:
	int number;
	int values[2] = { -1, -1 };
};

Bot::Bot() { }

Bot::Bot(int number) {
	this->number = number;
}

void Bot::addChip(int value) {
	if (this->values[0] == -1) {
		this->values[0] = value;
	} else {
		this->values[1] = value;
	}
}

bool Bot::isFull() {
	return (this->values[0] > -1 && this->values[1] > -1);
}

int Bot::getChip(magnitude_t mag) {
	auto lowIndex = (this->values[0] < this->values[1] ? 0 : 1);
	auto highIndex = (this->values[0] > this->values[1] ? 0 : 1);
	auto ret = -1;

	switch (mag) {
		case LOW:
			ret = this->values[lowIndex];
			this->values[lowIndex] = -1;
			break;
		case HIGH:
			ret = this->values[highIndex];
			this->values[highIndex] = -1;
			break;
	}

	return ret;
}

struct Instruction {
	magnitude_t chipType;
	destination_t destinationType;
	int destinationNumber;
};

struct Instructions {
	int sourceBotNumber;
	vector<Instruction> instructions;
};

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

void processQueue(vector<Instructions> &q, map<int, Bot> &bots, map<int, int> &output) {
	unsigned int i = 0;

	for (; i < q.size(); i++) {
		auto pair = q.at(i);

		// See if this bot has both chips and can do work
		auto bot = bots[pair.sourceBotNumber];
		if (!bot.isFull()) {
			continue;
		}

		// Find the min/max chip
		auto minChip = bot.getChip(LOW);
		auto maxChip = bot.getChip(HIGH);

		// Part A answer
		if (minChip == CHIP_B && maxChip == CHIP_A) {
			cout << "Bot " << pair.sourceBotNumber << " compares microchips with values " << CHIP_A << " and " << CHIP_B << "." << endl;
		}

		// Process the instructions
		for (auto i : pair.instructions) {
			auto value = (i.chipType == LOW ? minChip : maxChip);
			auto key = i.destinationNumber;

			switch (i.destinationType) {
				case OUTPUT:
					output[key] = value;
					break;
				case BOT:
					auto destBot = bots[key];
					destBot.addChip(value);

					bots[key] = destBot;
					break;
			}
		}

		// Remove this instruction from the queue and start over
		q.erase(q.begin() + i);
		i = 0;
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
	map<int, Bot> bots;
	map<int, int> output;
	vector<Instructions> q;

	for (auto line : input) {
		// Determine the instruction type
		if (line.substr(0, 5) == "value") {
			// If it's a value line, simply set the value
			auto bits = split(line, ' ');
			auto bot = stoi(bits[5]);
			auto value = stoi(bits[1]);

			auto it = bots.find(bot);

			if (it != bots.end()) {
				// Get the bot from the list and remove it
				Bot b = bots[bot];
				bots.erase(bot);

				// Add the chip
				b.addChip(value);

				// Put the bot back into the list
				bots[bot] = b;
			} else {
				Bot b(bot);
				b.addChip(value);

				bots[bot] = b;
			}
		} else {
			// Otherwise, sort it out and add it to our queue
			auto bits = split(line, ' ');

			auto givingBot = stoi(bits[1]);
			auto lowDestinationType = bits[5];
			auto lowDestinationNum = stoi(bits[6]);
			auto highDestinationType = bits[10];
			auto highDestinationNum = stoi(bits[11]);

			Instruction i1;
			i1.chipType = LOW;
			i1.destinationType = (lowDestinationType == "bot" ? BOT : OUTPUT);
			i1.destinationNumber = lowDestinationNum;

			Instruction i2;
			i2.chipType = HIGH;
			i2.destinationType = (highDestinationType == "bot" ? BOT : OUTPUT);
			i2.destinationNumber = highDestinationNum;

			Instructions p;
			p.sourceBotNumber = givingBot;
			p.instructions.push_back(i1);
			p.instructions.push_back(i2);

			q.push_back(p);
		}

		// Now that we've done a new instruction, see if we can do anything in our queue
		processQueue(q, bots, output);
	}

	// If we've made it through the file, keep going through the queue until it's complete
	while (q.size()) {
		processQueue(q, bots, output);
	}

	return 0;
}
