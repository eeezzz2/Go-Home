#include "Cards.h"
#include "Players.h"
#include <iostream>
#include <string>

extern vector<PlayerType> players;
using namespace std;
/* Cards() constructor initializes the card and their values in an array of Struct 'Face' values */
Cards::Cards() {
	Face values[10] = {{1,""},{1,""},{2,""},{2,""},{3,""},
			 {3,""},{4,""},{4,""},{0,"\t\t\tLOSE A TURN!\n"},
			 {0, "\t\t\tSWITCH PLACES WITH ANOTHER PLAYER\n"}};
	for(int i = 0; i < 10; i++)
		cards[i] = values[i];

}

/* pullCard() pulls a random card from the deck and prints it's value if it isn't an action card
	it returns the amount of spaces to move forward, or returns 60 for a "Switch Places" pull,
	0 for a "Lose Turn" pull
 */
int Cards::pullCard() {
	int random = rand() % 10;

	if(cards[random].forward != 0) {
		if(cards[random].forward > 1) {
			cout << "\t\t\t\t\t\t\t\t\t\t!MOVE FORWARD " << cards[random].forward << " SPACES!\n" << endl;
		}
		else {
			cout << "\t\t\t\t\t\t\t\t\t\t!MOVE FORWARD " << cards[random].forward << " SPACE!\n" << endl;
		}
	return cards[random].forward;
	}
	else {
		cout << cards[random].action << endl;
		if(cards[random].action == "\t\t\tSWITCH PLACES WITH ANOTHER PLAYER\n") {
			return 60;
		}
		else {
			return 0;
		}
	}
}

/* action() method is called to carry out the necessary actions of pulled action card
	@param: playerName, dummy (used to call Players methods
	@return: a string, either the player to switch, 'stay' for no switch, or an unused string called lost for losing a turn and to avoid 
	compilation errord
  */
string Cards::action(string playerName, int indicator, Players dummy) {
	int playerIndex = -1;
	int currentPosition = dummy.getPlace(playerName);
	if(indicator == 60) {
		cout << "\n\t\t\t\t\t\tDO YOU WANT TO SWITCH PLACES WITH ANOTHER PLAYER?" << "\n\t\t\t\t\t\tCURRENT PLAYER POSITIONS: " << endl;
		dummy.printCurrentPositions();
		cout << "\n\t\t\t\t\t\tENTER 'Y' TO SWITCH PLACES OR 'N' TO STAY WHERE YOU ARE: ";
		while(1) {
			string yesOrNo;
			cin >> yesOrNo;
			if(yesOrNo == "Y" || yesOrNo == "y") {
				cout << "\n\t\t\t\t\t\tWHICH PLAYER? ";
				string switchPlayer;
				cin >> switchPlayer;
				return switchPlayer;
			}
			else {
				playerName = "stay";
				cout << "\n\t\t\t\t\t\tYOU HAVE CHOSEN TO STAY " << (21 - currentPosition) <<  " SPACES AWAY FROM HOME" << endl;
				return playerName;
			}
		}
	}
	else if(indicator == 0) {
		cout << "\n\t~~~YOU HAVE LOST YOUR TURN. YOU ARE STILL " << (21 - currentPosition) << " SPACES AWAY FROM HOME." << " BETTER LUCK NEXT TIME~~~" << endl;
	}
	string lost = "LOST";
	return lost;
}

