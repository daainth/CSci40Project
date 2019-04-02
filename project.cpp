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
	rooms left;
	rooms right;
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

void execute(string, rooms&, roomType[NOROOM]);
void initialize(roomType[NOROOM]);

int main()
{
	string command;
	roomType room[NOROOM];
	rooms currentRoom;
	cout << "You have just awakened on a strange island with a terrible headache." << endl;
	cout << "You can't remember anything about yourself or where you are." << endl;
	cout << "Type 'help' to view instructions" << endl;
	//getline(cin, command);
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

void execute(std::string command, rooms& currentRoom, roomType room[NOROOM])
{
	rooms oldroom;
	oldroom = currentRoom;
	if (command == "south" or "s" or "down" or "d")
	{
		currentRoom = room[currentRoom].direction.south;
		room[currentRoom].returning = true;
	}
	else
	{
		if (command == "west" or "w" or "left" or "l")
		{
			currentRoom = room[currentRoom].direction.west;
			room[currentRoom].returning = true;
		}
		else
		{
			if (command == "north" or "w" or "up" or "u")
			{
				currentRoom = room[currentRoom].direction.north;
				room[currentRoom].returning = true;
			}
			else
			{
				if (command == "east" or "e" or "right" or "r")
				{
					currentRoom = room[currentRoom].direction.north;
					room[currentRoom].returning = true;
				}
			}
		}
	}
	if (currentRoom == NOROOM)
	{
		cout << "Nothing here, try a different direction." << endl;
		currentRoom = oldroom;
	}
	cout << "You are currently in room " << currentRoom << endl;

}

void initialize(roomType room[NOROOM])
{
	room[ISLAND].longd = " Long Desc   ";
	room[ISLAND].shortd = "    ";
	room[ISLAND].direction.north = NOROOM;
	room[ISLAND].direction.south = NOROOM;
	room[ISLAND].direction.west = NOROOM;
	room[ISLAND].direction.east = GANGPLANK;
	room[ISLAND].direction.up = NOROOM;
	room[ISLAND].direction.down = NOROOM;
	room[ISLAND].returning = false;

	room[GANGPLANK].longd = "  Long desc  ";
	room[GANGPLANK].shortd = "    ";
	room[GANGPLANK].direction.north = NOROOM;
	room[GANGPLANK].direction.south = NOROOM;
	room[GANGPLANK].direction.west = ISLAND;
	room[GANGPLANK].direction.east = UPPERDECK;
	room[GANGPLANK].direction.up = NOROOM;
	room[GANGPLANK].direction.down = NOROOM;
	room[GANGPLANK].returning = false;

	room[SHIPWHEEL].longd = "  Long desc  ";
	room[SHIPWHEEL].shortd = "    ";
	room[SHIPWHEEL].direction.north = NOROOM;
	room[SHIPWHEEL].direction.south = UPPERDECK;
	room[SHIPWHEEL].direction.west = NOROOM;
	room[SHIPWHEEL].direction.east = NOROOM;
	room[SHIPWHEEL].direction.up = NOROOM;
	room[SHIPWHEEL].direction.down = NOROOM;
	room[SHIPWHEEL].returning = false;

	room[UPPERDECK].longd = "  Long desc  ";
	room[UPPERDECK].shortd = "    ";
	room[UPPERDECK].direction.north = SHIPWHEEL;
	room[UPPERDECK].direction.south = CAPTAINQUARTERS;
	room[UPPERDECK].direction.west = GANGPLANK;
	room[UPPERDECK].direction.east = NOROOM;
	room[UPPERDECK].direction.up = NOROOM;
	room[UPPERDECK].direction.down = BOTTOMDECK;
	room[UPPERDECK].returning = false;

	room[BOTTOMDECK].longd = "  Long desc  ";
	room[BOTTOMDECK].shortd = "    ";
	room[BOTTOMDECK].direction.north = NOROOM;
	room[BOTTOMDECK].direction.south = BRIG;
	room[BOTTOMDECK].direction.west = CARGOHOLD;
	room[BOTTOMDECK].direction.east = GALLEY;
	room[BOTTOMDECK].direction.up = UPPERDECK;
	room[BOTTOMDECK].direction.down = NOROOM;
	room[BOTTOMDECK].returning = false;

	room[GALLEY].longd = "  Long desc  ";
	room[GALLEY].shortd = "    ";
	room[GALLEY].direction.north = NOROOM;
	room[GALLEY].direction.south = NOROOM;
	room[GALLEY].direction.west = BOTTOMDECK;
	room[GALLEY].direction.east = NOROOM;
	room[GALLEY].direction.up = NOROOM;
	room[GALLEY].direction.down = NOROOM;
	room[GALLEY].returning = false;

	room[BRIG].longd = "  Long desc  ";
	room[BRIG].shortd = "    ";
	room[BRIG].direction.north = BOTTOMDECK;
	room[BRIG].direction.south = NOROOM;
	room[BRIG].direction.west = CARGOHOLD;
	room[BRIG].direction.east = GALLEY;
	room[BRIG].direction.up = NOROOM;
	room[BRIG].direction.down = NOROOM;
	room[BRIG].returning = false;

	room[CAPTAINQUARTERS].longd = "  Long desc  ";
	room[CAPTAINQUARTERS].shortd = "    ";
	room[CAPTAINQUARTERS].direction.north = UPPERDECK;
	room[CAPTAINQUARTERS].direction.south = NOROOM;
	room[CAPTAINQUARTERS].direction.west = NOROOM;
	room[CAPTAINQUARTERS].direction.east = NOROOM;
	room[CAPTAINQUARTERS].direction.up = NOROOM;
	room[CAPTAINQUARTERS].direction.down = NOROOM;
	room[CAPTAINQUARTERS].returning = false;

	room[CARGOHOLD].longd = "  Long desc  ";
	room[CARGOHOLD].shortd = "    ";
	room[CARGOHOLD].direction.north = NOROOM;
	room[CARGOHOLD].direction.south = NOROOM;
	room[CARGOHOLD].direction.east = BOTTOMDECK;
	room[CARGOHOLD].direction.west = NOROOM;
	room[CARGOHOLD].direction.up = NOROOM;
	room[CARGOHOLD].direction.down = NOROOM;
	room[CARGOHOLD].returning = false;

}
