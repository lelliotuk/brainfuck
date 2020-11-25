#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


struct Cell {
	char val;
	struct Cell* prev;
	struct Cell* next;
};


int main(int argc, char* argv[]) {

	if (argc == 1) {
		cout << "Usage:\nbf FILE\nUse '-' for stdin\n\n";
		return 0;
	}

	string inputProgram;
	ostringstream ss;
	cout << argv[1];
	if (strcmp(argv[1], "-") == 0) {
		ss << cin.rdbuf();
	} else {
		ifstream f(argv[1]);
		if (f) {
			ss << f.rdbuf();
		}
		else {
			cout << "Not a file";
			return 1;
		}
	}

	inputProgram = ss.str();


	string program;

	// strip comments
	for (char c : inputProgram) { 
		if (c == '+' ||
			c == '-' ||
			c == '<' ||
			c == '>' ||
			c == '.' ||
			c == ',' ||
			c == '[' ||
			c == ']' ) {
			program += c;
		}
	}


	int *loopPairs;
	loopPairs = new int[program.length()];

	unsigned int progPtr = 0;

	struct Cell* cellPtr = new Cell{ 0,nullptr,nullptr };

	// find loop pairs
	while (progPtr < program.length()) {
		if (program[progPtr] == '[') {
			int left = progPtr;

			int loopDepth = 1;
			while (loopDepth) {
				progPtr++;
				if (progPtr == program.length()) {
					cout << "!! Missing matching ']' at command " << left;
					return 1;
				}
				if (program[progPtr] == '[') loopDepth++;
				if (program[progPtr] == ']') loopDepth--;
			}
			int right = progPtr;
			
			loopPairs[left] = right;
			loopPairs[right] = left;
			progPtr = left;
		} 
		progPtr++;
	}

	progPtr = 0;

	// program loop
	while (progPtr >= 0 && progPtr < program.length()) {
		switch (program[progPtr]) {

		case '<':
			if (!cellPtr->prev) {
				cellPtr->prev = new Cell{ 0, nullptr, cellPtr };
			}
			cellPtr = cellPtr->prev;
			break;


		case '>':
			if (!cellPtr->next){
				cellPtr->next = new Cell{ 0, cellPtr, nullptr };
			}
			cellPtr = cellPtr->next;
			break;


		case '-':
			cellPtr->val--;
			break;


		case '+':
			cellPtr->val++;
			break;


		case '.':
			cout << cellPtr->val;
			break;


		case ',':
			cin >> cellPtr->val;
			break;


		case '[':
			if (!cellPtr->val) {
				progPtr = loopPairs[progPtr];
			}
			break;


		case ']':
			if (cellPtr->val) {
				progPtr = loopPairs[progPtr];
			} 
			break;

		}
		progPtr++;
	}
}
