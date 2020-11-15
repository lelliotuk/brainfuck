#include <iostream>
#include <string>

using namespace std;

struct Cell {
	uint8_t val;
	struct Cell* prev;
	struct Cell* next;
};


string program = "-[------->+<]>-.-[->+++++<]>++.+++++++..+++.[--->+<]>-----.--[->++++<]>-.--------.+++.------.--------.";


int main() {

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
					cout << "!! Missing matching ']' at char " << left;
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
			cout << (char)cellPtr->val;
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
