#include "Board.h"
#include "Players.h"
#include <iostream>
#include <vector>
#include <string>

extern vector<PlayerType> players;
using namespace std;
/* Board() constructor adds values to each space in spaces vector (declared in header file)  */
Board::Board() {
	for(int i = 0; i < 22; i++) {
		if(i == 0) {
			spaces[0] = "start";
		}
		else if(i == 3) {
			spaces[i] = "2";
		}
		else if(i == 6) {
			spaces[i] = "1";
		}
		else if(i == 8) {
			spaces[i] = "3";
		}
		else if(i == 14) {
			spaces[i] = "2";
		}
		else if(i == 18) {
			spaces[i] = "2";
		}
		else if(i == 20) {
			spaces[i] = "1";
		}
		else if(i >= 21) {
			spaces[i] = "GAME OVER!!! YOU WIN!!!";
		}
		else {
			spaces[i] = "empty";
		}
	}
}

/* getSpace() returns the obstacles of the space that a user has moved to after pulling a card  */
int Board::getSpace(int position) {

	if(spaces[position] == "empty") {
		cout << "\t~~~EMPTY SPACE: NO OBSTACLES. YOU ARE NOW " << (21 - position) << " SPACES FROM HOME~~~" << endl;
		return position;
	}
	else if(spaces[position] == "GAME OVER!!! YOU WIN!!!") {
		cout << spaces[position] << endl;
		return 100;
	}
	else {
		int decrements = stoi(spaces[position]);
		position -= decrements;
		if(position <= 0) {
			position = 0;
			cout << "\t~~~YOU HAVE RETURNED TO THE STARTING POSITION~~~" << endl;
			return position;
		}
		else {
			cout << "\t~~~OBSTACLE! YOU ARE BEING MOVED BACK " << decrements << " SPACES. YOU ARE NOW " << (21 - position) << " SPACES FROM HOME~~~" << endl;
			return position;
		}
	}
	return position;
}

