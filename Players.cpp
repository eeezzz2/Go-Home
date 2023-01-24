#include "Players.h"
#include <iostream>
#include <vector>


using namespace std;


/* Players() constructor takes in parameters name and place and adds a new player using those values (which come from user input).
	It prompts the user to select a game piece from 4 declared pieces (rook, pawn, bishop, knight).
		Each time a game piece is selected by a user, it is taken away as a future option for other players.
  */
Players::Players(string name, int place): name(name), place(place) {
	addPlayer(name, place);
	int error = -1;
	string piece;
	while(error == -1){
		cout << "\n\tCURRENT PIECES:         * ";
		for(int j = 0; j < pieces.size(); j++) {
			cout << pieces[j] << " * ";
		}
		cout << endl;
		cout << "\nPLEASE SELECT YOUR BOARD PIECE: ";
		cin >> piece;
		for(char &ch: piece) {
			ch = to_upper(ch);
		}
		for(int k = 0; k < pieces.size(); k++) {
			if(piece == pieces[k]) {
				error = 2;
			}
		}
		if(error == -1)
			cout << "\n\t\t\t\t!INVALID SELECTION. PLEASE CHECK YOUR INPUT. IT IS NOT CASE SENSITIVE!" << endl;
	}

	decrementPieces(piece, name);
}

/* addPlayer() takes parameters in from Players() constructor and adds a PlayerType object to the vector 'players' */
void Players::addPlayer(string name, int place) {
	PlayerType p;
	p.name = name;
	p.place = place;
	players.push_back(p);
}

/* printVector() prints the 'players' vector to standard output  */
void Players::printVector() {
	cout << "\n\n\n\n\n\t\t\t\t\t\t```'''---------.........-----------~~~~~~~~~------~~--" << endl;
	for(int i = 0; i < players.size(); i++) {
		int space = (8 - players[i].name.size());
		int pieceSpace = ((8 - players[i].piece.size()) / 2);
		string nameSpace, midSpace;
		for(int i = 0; i < space; i++)
			nameSpace += " ";
		for(int i = 0; i < pieceSpace; i++)
			midSpace += " ";
		cout << "\t\t\t\t\t\tPLAYER " << i << ": " << players[i].name << nameSpace  << "||" << midSpace << players[i].piece <<  midSpace << " ||" << nameSpace << "SPACES TO WIN: " << 21 - players[i].place << endl;
	}
	cout << "\t\t\t\t\t\t------~~~~~~~~~~----------------.........----~~--'''```\n\n\n\n\n" << endl;
}

/* printCurrentPositions() is a simpler printout of the scoreboard used only if a switch places card is drawn  */
void Players::printCurrentPositions() {
	for(int i = 0; i < players.size(); i++) {
		if(i < players.size() - 1) {
			cout << "\n\t\t\t\t\t\t" << players[i].name << ": " << players[i].place << " (" << (21 - players[i].place) << " SPACES TO WIN)";
		}
		else {
			cout << "\n\t\t\t\t\t\t" << players[i].name << ": " << players[i].place << " (" << (21 - players[i].place) << " SPACES TO WIN)\n";
		}
	}
}

/* nextPlayer() returns the next player, after some initialization on first call, and prints the numerical representation of how many turns the game has had   */
string Players::nextPlayer() {
	if(initialized == false) {
		counter = 0;
		index = 0;
		initialized = true;
	}
	if(counter == 0) {
		counter++;
		cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t~~~" << counter << "ST MOVE~~~" << endl;
		counter++;
		return players[index].name;
	}
	if(counter == 2 || counter == 22 || counter == 32 || counter == 42) {
		cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t~~~" << counter << "ND MOVE~~~" << endl;
		counter++;
	}
	else if(counter == 3 || counter == 23 || counter == 33 || counter == 43) {
		cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t~~~" << counter << "RD MOVE~~~" << endl;
		counter++;
	}
	else {
		cout << "\n\n\n\t\t\t\t\t\t\t\t\t\t~~~" << counter << "TH MOVE~~~" << endl;
		counter++;
	}

	if(index == players.size() - 1)
		index = -1;

	index++;
	return players[index].name;
}

/* getPlace() returns a players current place and is defined twice to except either a vector index (int) or a player name (string)  */
int Players::getPlace(int index) {
	return players[index].place;
}

int Players::getPlace(string name) {
	for(int i = 0; i < players.size(); i++) {
		if(name == players[i].name)
			return players[i].place;
	}
	return -1;
}

/* movePlaces() is the initial method used to move a player forward by the number of places specified from card pull  */
void Players::movePlaces(int index, int placesForward) {
	players[index].place += placesForward;
}

/* updatePosition() is used after the obstacles are accounted for and the player's position needs to be changed  */
void Players::updatePosition(int index, int position) {
	players[index].place = position;
}

// to_upper() method used to accomodate different case types with user input, and assures no mismatch with program data variables
char Players::to_upper(char ch) {
	if(ch >= 'a' && ch <= 'z') {
		return ch -32;
	}
	return ch;
}

//initializer variable set to false, and changes to true after the game is properly set up
bool Players::initialized = false;

/* decrementPieces() is called in the constructor to make sure no user can choose the same game piece. it also formats the players.piece string value  */
void Players::decrementPieces(string piece, string playerName) {
	int index = 0;
	while(piece != pieces[index]) {
		index++;
	}
	for(int i = 0; i < players.size(); i++) {
		if(playerName == players[i].name) {
			players[i].piece = " (";
			players[i].piece += piece;
			players[i].piece += ")";
		}
	}
	pieces.erase(pieces.begin()+index);
}

/* switchPlaces() method use for changing the place values of two players. once the switch happens, both player's place information is printed  */
void Players::switchPlaces(string player, int playerPlace, string switchPlayer, int switchPlace) {
int playerOriginal = playerPlace;
int index1, index2;
	for(int i = 0; i < players.size(); i++) {
		if(player == players[i].name) {
			index1 = i;
			updatePosition(i, switchPlace);
			int newPlace = players[i].place;
			cout << "\n\t~~~" << player << " SWITCHED PLACES WITH " << switchPlayer << " AND IS NOW " << (21 - newPlace) << " PLACES AWAY FROM WINNING~~~" << endl;
		}
	}
	for(int i = 0; i < players.size(); i++) {
		if(switchPlayer == players[i].name) {
			index2 = i;
			updatePosition(i, playerOriginal);
			int newPlace = players[i].place;
			cout << "\n\t~~~" << switchPlayer << " SWITCHED PLACES WITH " << player << " AND IS NOW " << (21 - newPlace) << " PLACES AWAY FROM WINNING~~~" << endl;
		}
	}

}

