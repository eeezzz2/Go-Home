#include "Cards.h"
#include "Players.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std::chrono_literals; // used for stalling standard output by seconds
/* vector of PlayerType players is a global variable declared and initialized in Players() class - i
the vector holds players and their data in an array of struct. 
*/
extern vector<PlayerType> players;
// extern vector<string> spaces;
/* introduction() prints out game instructions in the middle of asci rendition of the game board  */
void introduction() {
	cout <<
",,,,,,,,,,,,,:,,,,,,,,,,,:,,,,,,,,,,,:,,,,,,,,,,,:,,,,,,,,,,,,:,,,,,,,,,,,,,,,,,,,,,,,,:,,,,,,,,,,,,\n"
",............,...........,...........,...........,............,...........,,...........,...........,\n"
",.....,,.....,...........,...........,...........,......;:....,...........,,...........,...........,\n"
",.....+;.....,...........,...........,...........,.....,*:....,...........,,...........,...........,\n"
",....,;:,....,...........,...........,...........,.....::,,...,...........,,...........,...........,\n"
",....:+,:....,...........,...........,...........,.....**;:...,...........,,...........,...........,\n"
",....*S+;....,........<<<<<<<<<......,...........,....,?%%;...,...........,,........<<<<<<<<<<<<...,\n"
",....+**:,...,...........,...........,...........,....:+;+::..,...........,,...........,.......^...,\n"
",..:+*?+;*:,.,...........,...........,...........,..:+?*?*+*;,,...........,,...........,.......^...,\n"
",.;*?%?;:?*;.,...........,...........,...........,.,**%?+,;?*;,...........,,...........,.......^...,\n"
",.:+??+;;?+:.,...........,...........,...........,..;+?*+;+?+,,...........,,...........,.......^...,\n"
",..,;*;;*+,..,...........,...........,...........,...,+*;;*;,.,...........,,...........,.......^...,\n"
",....:+;:...,,...........,...........,...........,.....:+:,...,,..........,,...........,.......^...,\n"
",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
",.....v......,.........................................................................,...........,\n"
",.....v......,.........................................................................,...........,\n"
",.....v......,.........................................................................,...........,\n"
",.....v......,.........................................................................,...........,\n"
",.....v......,.........................................................................,...........,\n"
",.....v......,.......................................... GoHome! ......................,...........,\n"
",.....v......,................................................... GoHome! .............,...........,\n"
",............,............................................................ GoHome! ....,...........,\n"
",............,.........................................................................,...........,\n"
"............,.............. PLAYERS: 2-4 players ......................................,...........,\n"
",............,.... OBJECT: Reach the last space on the board, which is labeled 'Home.' ,...........,\n"
",............,....... TO BEGIN: Player with shortest first name goes first. ...........,...........,\n"
":,,,,,,,,,,,,,.......... TO PLAY: Players take turns in order until one player wins ,,,,,,,,,,,,,,,,\n"
",...........,,......... A turn consists of picking a card. ............................,...........,\n"
",.....:;.....,....... If the card has a number, the player moves that number of spaces ,...........,\n"
"...........,......., If the card says 'lose turn,' the player does nothing, ...........,...........,\n"
",.....;;,....,.... and the game continues with the next player. .......................,...........,\n"
",.....;,,....,... If the card says 'switch places,' the player must switch places .....,...........,\n"
",....:?+;,...,.. with a player of its choice ..........................................,...........,\n"
",....;?%+,...,. If the player lands on a space with a number ..........................,...........,\n"
",...,+;*;;,.., the player moves back that number of spaces ............................,...........,\n"
",.,+*%**;**;,,.........................................................................,...........,\n"
",.:**%?;,**+,,.........................................................................,...........,\n"
",..,+?+;+?+,.,.........................................................................,...........,\n"
",....;+:;:...,.........................................................................,...........,\n"
",,,,,,,:,,,,,,.........................................................................,,,,,,,,,,,,,\n"
",,,:;:;;:,,,,,.........................................................................,,,,,,.,,,,,,\n"
",..,;::;:..H.,.........................................................................,.....:,....,\n"
",.:;::;,...O.,.........................................................................,....,*:....,\n"
",.:::;;,...M,,.........................................................................,....,;,,...,\n"
";;:;**;?:?+E;,.........................................................................,....++::...,\n"
";???+.???%**:,.........................................................................,...,???;...,\n"
";+;+*++*+***:,.........................................................................,...,+;?+,..,\n"
",,,,,:H,.,,::,.........................................................................,.,;**++**:,,\n"
",.....O.....,..........................................................................,.+*%%*:;?*:,\n"
",.....M......,.........................................................................,.:+??+;+?;,,\n"
",.....E......,.........................................................................,..,;*;;+:..,\n"
",.....!......,.........................................................................,....,;:,...,\n"
",,,,,,,YOU,WIN,!!!,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n"
",............,...........,...........,...........,,...........,,..........,,...........,...........,\n"
",............,...........,...........,......,....,,...........,,..........,,.....,.....,.........^.,\n"
",...-->>>>>..,...........,...........,.....;;....,,...........,,..........,,....,+,....,.........^.,\n"
",.START......,...........,...........,.....+:,...,,...........,,..........,,....:;,....,.........^.,\n"
",,:,,,::.>>>>>>>>>.......,...........,....,++:...,,...........,,..........,,....;::,...,.........^.,\n"
",:;:;+;:.....,...........,...........,....+???...,,...........,,..........,,...,?*;:...,.........^.,\n"
",,,,,,,:.....,...........,...........,....+**+,..,,...........,,..........,,...:***:...,.........^.,\n"
",..;***?+....,...........,...........,..,;*;+;+,.,,...........,,..........,,..:++;*+;,.,.........^.,\n"
",..:+++*;....,...........,...........,.:*?%*::?*;,,...........,,..........,,,+*%?*+*?+,,.>>>>>>>>>.,\n"
",......,.....,...........,...........,.:+??*;;?*:,,...........,,..........,,,+*%?+:*?+,,...........,\n" << endl;

cout << "   PLEASE OPEN YOUR TERMINAL WINDOW TO FULL SCREEN FOR THE ENTIRETY OF THE GAME AND TAKE A MINUTE\n   TO READ THE GAME INSTRUCTIONS ABOVE.\n" << endl;
this_thread::sleep_for(2s); // wait 2 seconds

}
// to_upper(char) is used for converting each character of a string to uppercase to prevent mismatch of user input with program data
char to_upper(char ch) {
        if(ch >= 'a' && ch <= 'z') {
                return ch -32;
        }
        return ch;
}
/* main() first prints out the introduction, and then initializes Board and Cards class
	objects to build the game board, create the cards and assign values. It then sets
	up the players by using user input to initiale Players type with name, initial
	place = 0. Once all the players are initialized, the global vector players that
	stores all of their info is printed using printVector() method. The game then
	begins. Each player pulls a card using cards.pullCard() method, which returns
	a value of spaces to move forward. a card can alsoe return a 0 or 60, which
	indicate a lost turn or a switch places card respectively. getPlace() is used to
	return the players current place on the board, initially not accounting for
	any obstacles that the space holds. getSpace() is then called to return any
	obstacles. the player positions are updated according to the returned obstacles
	or if a user switches places with another user. the game continues in a while loop
	until the value 100 is returned after a move to the last space.
  */
int main() {
        introduction();
        Board board;
        Cards cards;
        bool winner = false;
        int numPlayers;
        cout << "\n....................." << endl;
        this_thread::sleep_for(1s);
        cout << "\n\nHOW MANY PLAYERS? (2 - 4): ";
        cin >> numPlayers;
        cout << "\nPLAYER WITH THE SHORTEST NAME WILL GO FIRST. ENTER PLAYER ONE'S NAME: ";
        int initPlace = 0;
        string name;
        cin >> name;
        for (char &ch: name) {
                ch = to_upper(ch);
        }
        Players player(name, initPlace);
        for(int i = 0; i < numPlayers - 1; i++) {
                if(i + 1 < numPlayers)
                        cout << "\nENTER NEXT PLAYER\'S NAME: ";
                cin >> name;
                for (char &ch: name) {
                        ch = to_upper(ch);
                }
                Players player(name, initPlace);
        }
        player.printVector();
        string currentPlayer = player.nextPlayer();
        int index = -1;
        while(winner == false) {
                if (index == (numPlayers - 1)) {
                        index = 0;
                        cout << "\n\nPLAYER " << index;
                }
                else {
                        index++;
                        cout << "\n\nPLAYER " << index;
                }
                cout <<": " << currentPlayer << ", IT\'S YOUR TURN! (ENTER s FOR SCOREBOARD, c TO DRAW A CARD, or x TO QUIT: ";
                while(1) {
                        char c;
                        cin >> c;
                        c = to_upper(c);
                        if(c == 'C') {
                                break;
                        }
                        else if(c == 'X') {
                                exit(0);
                        }
                        else if(c == 'S') {
                                player.printVector();
                        }
		        else {
                                cout << "ERROR: ENTER 'C' TO CONTINUE OR 'X' TO QUIT: ";
                        }
                }
                cout << "\n\n...PULLING A CARD FROM THE DECK AT RANDOM..." << endl;
                cout << "   ...";
                cout << "\n\t ...";
                cout << "\n\t\t...\n";
                this_thread::sleep_for(1s);
                int places = cards.pullCard();

                if(places != 60 && places != 0) {
                        player.movePlaces(index, places);
                        int position = player.getPlace(index);
                        position = board.getSpace(position);
                        if(position == 100) {
                                this_thread::sleep_for(1s);
                                for(int i = 0; i < 100; i++)
                                        cout << "!!!!!" << currentPlayer << " WINS!!!!!!!!!!!!!!!!!!!!" << currentPlayer << " WINS!!!!!!!!!!!!!!!!!!!!!" << currentPlayer << "WINS!!!!!!!!!!!!!!!!!!!!!!!!!";
                                winner = true;
                                currentPlayer = player.nextPlayer();
                                exit(0);
                                }
                        player.updatePosition(index, position);
                }
                else if(places == 60) {
                        int currentPlayerPosition = player.getPlace(index);
                        string switchPlayer = cards.action(currentPlayer, places, player); // cards.action() is used for action cards, either "Lose a turn" or "Switch Places"
                        for(char &ch: switchPlayer)
                                ch = to_upper(ch);
                        int switchPlayerPosition = player.getPlace(switchPlayer);
                        if(switchPlayer != "stay" && switchPlayer != "STAY") {
                                player.switchPlaces(currentPlayer, currentPlayerPosition, switchPlayer, switchPlayerPosition);
                        }
                        else {
                                cout << "\n\t~~~" << currentPlayer << " CHOSE TO NOT SWITCH PLACES WITH ANOTHER PLAYER AND IS CURRENTLY " << (21 - currentPlayerPosition) << " PLACES FROM HOME~~~" << endl;
                        }
                }
                else if(places == 0) {
                        cards.action(currentPlayer, places, player);
                }
                player.printVector();
                currentPlayer = player.nextPlayer(); // next player in the vector becomes current player
        }
}
