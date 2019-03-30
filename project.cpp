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
enum rooms { TREE, ISLAND, GANGPLANK, UPPERDECK, SHIPWHEEL, BOTTOMDECK, GALLEY, BRIG, CAPTAINQUARTERS, CARGOHOLD, NOROOM };
struct movement {
	rooms north;
	rooms south;
	rooms east;
	rooms west;
	rooms up;
	rooms down;
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

void execute(string,rooms,roomType);
void initialize(rooms);

int main()
{
	string command;
	roomType room[NOROOM];
	rooms currentRoom;
	cout << "You have just awakened on a strange island with a terrible headache." << endl;
	cout << "You can't remember anything about yourself or where you are." << endl;
	cout << "Type 'help' to view instructions" << endl;
	getline(cin, command);
	gameOver = command == "quit";
	currentRoom = ISLAND;
	initialize(room);
	while (not gameOver)
		//while(command != "quit")
	{
		execute(command, currentRoom, room);
		getline(cin, command);
		gameOver = command == "quit";
	}
	cout << "Done" << endl;


	return 0;
}

void execute(string command, rooms currentRoom, roomType room[NOROOM])
{
	cout << command << " executed" << endl;
}

void initialize(roomType rooms[NOROOM])
{
	rooms[ISLAND].longd = " Long Desc   ";
	rooms[ISLAND].shortd = "    ";
	rooms[ISLAND].direction.north = NOROOM;
	rooms[ISLAND].direction.south = NOROOM;
	rooms[ISLAND].direction.west = NOROOM;
	rooms[ISLAND].direction.east = GANGPLANK;
	rooms[ISLAND].direction.up = NOROOM;
	rooms[ISLAND].direction.down = NOROOM;
	rooms[ISLAND].returning = false;

	rooms[GANGPLANK].longd = "  Long desc  ";
	rooms[GANGPLANK].shortd = "    ";
	rooms[GANGPLANK].direction.north = NOROOM;
	rooms[GANGPLANK].direction.south = NOROOM;
	rooms[GANGPLANK].direction.west = ISLAND;
	rooms[GANGPLANK].direction.east = UPPERDECK;
	rooms[GANGPLANK].direction.up = NOROOM;
	rooms[GANGPLANK].direction.down = NOROOM;
	rooms[GANGPLANK].returning = false;

	rooms[SHIPWHEEL].longd = "  Long desc  ";
	rooms[SHIPWHEEL].shortd = "    ";
	rooms[SHIPWHEEL].direction.north = NOROOM;
	rooms[SHIPWHEEL].direction.south = UPPERDECK;
	rooms[SHIPWHEEL].direction.west = NOROOM;
	rooms[SHIPWHEEL].direction.east = NOROOM;
	rooms[SHIPWHEEL].direction.up = NOROOM;
	rooms[SHIPWHEEL].direction.down = NOROOM;
	rooms[SHIPWHEEL].returning = false;

	rooms[UPPERDECK].longd = "  Long desc  ";
	rooms[UPPERDECK].shortd = "    ";
	rooms[UPPERDECK].direction.north = SHIPWHEEL;
	rooms[UPPERDECK].direction.south = CAPTAINQUARTERS;
	rooms[UPPERDECK].direction.west = GANGPLANK;
	rooms[UPPERDECK].direction.east = NOROOM;
	rooms[UPPERDECK].direction.up = NOROOM;
	rooms[UPPERDECK].direction.down = BOTTOMDECK;
	rooms[UPPERDECK].returning = false;

	rooms[BOTTOMDECK].longd = "  Long desc  ";
	rooms[BOTTOMDECK].shortd = "    ";
	rooms[BOTTOMDECK].direction.north = NOROOM;
	rooms[BOTTOMDECK].direction.south = BRIG;
	rooms[BOTTOMDECK].direction.west = CARGOHOLD;
	rooms[BOTTOMDECK].direction.east = GALLEY;
	rooms[BOTTOMDECK].direction.up = UPPERDECK;
	rooms[BOTTOMDECK].direction.down = NOROOM;
	rooms[BOTTOMDECK].returning = false;

	rooms[GALLEY].longd = "  Long desc  ";
	rooms[GALLEY].shortd = "    ";
	rooms[GALLEY].direction.north = NOROOM;
	rooms[GALLEY].direction.south = NOROOM;
	rooms[GALLEY].direction.west = BOTTOMDECK;
	rooms[GALLEY].direction.east = NOROOM;
	rooms[GALLEY].direction.up = NOROOM;
	rooms[GALLEY].direction.down = NOROOM;
	rooms[GALLEY].returning = false;

	rooms[BRIG].longd = "  Long desc  ";
	rooms[BRIG].shortd = "    ";
	rooms[BRIG].direction.north = BOTTOMDECK;
	rooms[BRIG].direction.south = NOROOM;
	rooms[BRIG].direction.west = CARGOHOLD;
	rooms[BRIG].direction.east = GALLEY;
	rooms[BRIG].direction.up = NOROOM;
	rooms[BRIG].direction.down = NOROOM;
	rooms[BRIG].returning = false;

	rooms[CAPTAINQUARTERS].longd = "  Long desc  ";
	rooms[CAPTAINQUARTERS].shortd = "    ";
	rooms[CAPTAINQUARTERS].direction.north = UPPERDECK;
	rooms[CAPTAINQUARTERS].direction.south = NOROOM;
	rooms[CAPTAINQUARTERS].direction.west = NOROOM;
	rooms[CAPTAINQUARTERS].direction.east = NOROOM;
	rooms[CAPTAINQUARTERS].direction.up = NOROOM;
	rooms[CAPTAINQUARTERS].direction.down = NOROOM;
	rooms[CAPTAINQUARTERS].returning = false;

	rooms[CARGOHOLD].longd = "  Long desc  ";
	rooms[CARGOHOLD].shortd = "    ";
	rooms[CARGOHOLD].direction.north = NOROOM;
	rooms[CARGOHOLD].direction.south = NOROOM;
	rooms[CARGOHOLD].direction.east = BOTTOMDECK;
	rooms[CARGOHOLD].direction.west = NOROOM;
	rooms[CARGOHOLD].direction.up = NOROOM;
	rooms[CARGOHOLD].direction.down = NOROOM;
	rooms[CARGOHOLD].returning = false;

}
