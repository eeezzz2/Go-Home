#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>

using namespace std;

static vector<string> spaces(22); // global vector to hold the values of each space on the board
class Board {
	public:
		Board(); // default constructor
		int getSpace(int position);
};
#endif
