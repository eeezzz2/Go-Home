#ifndef CARDS_H
#define CARDS_H
#include "Players.h"
#include <iostream>

using namespace std;

class Cards {
	private:
		// Face type hold the amount of spaces to move forward in a card pull, as well as any action to perform / otherwise "nothing"
		struct Face {
			int forward;
			string action = "nothing";
		};
		Face cards[10]; // an array of Face type, this is the deck of cards
	public:
		Cards(); // constructor
		int pullCard();
		string action(string, int, Players);
};
#endif


