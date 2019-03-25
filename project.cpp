//Group 5
/*Leonard Mejia
Joseph Alvarez
David Inthavong
Vanessa S.
Diego Denis-Arrue
*/
/*Group project island game that your goal is to leave the island */


#include <iostream>
#include <fstream>
#include <iso646.h>
#include <string>
using namespace std;
bool gameOver = false;

//Eventually possibly include "Ocean" to rooms
enum rooms { TREE, ISLAND, UPPERDECK, SHIPWHEEL, BOTTOMDECK, GALLEY, BRIG, CAPTAINQUARTERS, CARGOHOLD, NOROOM };
struct movement {
	rooms north;
	rooms south;
	rooms east;
	rooms west;
};
struct itemlist {
	bool knife;
	bool bananas;
	bool treasure;
	bool keys;
	bool prisonor;
};
struct roomType {
	string longd; //Long description
	string shortd; //Short description
	movement direction;
	itemlist item;
	bool returning;//Checks if user has been here before for the descriptions

};

void execute(string);


int main()
{
	string command;
	roomType room[NOROOM];
	cout << "You have just awakened on a strange island with a terrible headache." << endl;
	cout << "You can't remember anything about yourself or where you are." << endl;
	cout << "Type 'help' to view instructions" << endl;
	getline(cin, command);
	gameOver = command == "quit";
	while (not gameOver)
		//while(command != "quit")
	{
		execute(command);
		getline(cin, command);
		gameOver = command == "quit";
	}
	cout << "Done" << endl;


	return 0;
}

void execute(string command)
{
	cout << command << " executed" << endl;
}
