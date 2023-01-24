#ifndef PLAYERS_H
#define PLAYERS_H
#include <iostream>
#include <vector>

using namespace std;

static vector<string> pieces {"ROOK", "PAWN", "KNIGHT", "BISHOP"};
static int counter;
struct PlayerType {
	string name;
	int place;
	string piece;
};
static vector<PlayerType> players;
static int index;
class Players {
	public:
		string name;
		int place;
		Players(string, int);
		static bool initialized;
		void addPlayer(string, int);
		void printVector();
		void printCurrentPositions();
		string nextPlayer();
		string getName(Players);
		int getPlace(int);
		int getPlace(string);
		void movePlaces(int, int);
		void updatePosition(int, int);
		void switchPlaces(string, int, string, int);
		char to_upper(char);
		void decrementPieces(string, string);

};
#endif
