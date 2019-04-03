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

struct itemlist {
	bool knife;
	bool bananas;
	bool treasure;
	bool keys;
	bool prisonor;
};
struct movement {
	rooms north;
	rooms south;
	rooms east;
	rooms west;
	rooms up;
	rooms down;
};
struct roomType {
	string longd; //Long description
	string shortd; //Short description
	movement direction;
	itemlist item;
	bool returning;//Checks if user has been here before for the descriptions
};

struct currentRoom {
	itemlist items;
};


void initialize(roomType[NOROOM]);    // Has to be roomtype[NOROOM] for some reason

void execute(string, rooms&, rooms, roomType[NOROOM]); // roomType has an & next to it because we need the function to return the current room

int main()
{
	string command;
	roomType room[NOROOM];
	rooms currentRoom, lastRoom;
	command = "empty";

	initialize(room);                        // initialize sets everything up from the start of the game
	lastRoom = currentRoom = ISLAND;

	cout << "You have just awakened on a strange island with a terrible headache." << endl;
	cout << "You can't remember anything about yourself or where you are." << endl;
	cout << "Type 'help' to view instructions" << endl;
	cout << endl;
	gameOver = command == "quit";

	while (not gameOver)
	{
		if (room[currentRoom].returning)
		{
			cout << room[currentRoom].shortd << endl;
		}
		else
		{
			cout << room[currentRoom].longd << endl;
		}


		getline(cin, command);
		execute(command, currentRoom, lastRoom, room);

		if (currentRoom == NOROOM)    // NOROOM is used when you cannot go into an area
		{
			cout << "You can't go that way" << endl;
			currentRoom = lastRoom;  //Sets current room to whatever room you were in before
		}

		lastRoom = currentRoom;
		gameOver = command == "quit";

	}
	return 0;
}


// This needs to be rewritten because it only works with one word at the moment
void execute(string command, rooms& currentRoom, rooms lastRoom, roomType rooms[NOROOM])
{
	if (command == "south" or command == "s")
	{
		currentRoom = rooms[currentRoom].direction.south;
	}
	if (command == "east" or command == "e")
	{
		currentRoom = rooms[currentRoom].direction.east;
	}
	if (command == "west" or command == "w")
	{
		currentRoom = rooms[currentRoom].direction.west;
	}
	if (command == "north" or command == "n")
	{
		currentRoom = rooms[currentRoom].direction.north;
	}
	if (command == "up" or command == "u")
	{
		currentRoom = rooms[currentRoom].direction.up;
	}
	if (command == "down" or command == "d")
	{
		currentRoom = rooms[currentRoom].direction.down;
	}

	if (currentRoom == NOROOM)    // NOROOM is used when you cannot go into an area
	{
		cout << "You can't go that way" << endl;
		currentRoom = lastRoom;  //Sets current room to whatever room you were in before
	}

	rooms[lastRoom].returning = true;

}


void initialize(roomType rooms[NOROOM])
{
	rooms[TREE].longd = "There is a large banana tree here. (There is one bunch of ripe bananas on the tree within reach.)";
	rooms[TREE].shortd = "You are at the tree";
	rooms[TREE].direction.north = NOROOM;
	rooms[TREE].direction.south = NOROOM;
	rooms[TREE].direction.west = NOROOM;
	rooms[TREE].direction.east = ISLAND;
	rooms[TREE].direction.up = NOROOM;
	rooms[TREE].direction.down = NOROOM;
	rooms[TREE].returning = false;

	rooms[ISLAND].longd = "The island is forested with banana trees. Most of the bananas are green, but one tree to your west might have ripe bananas. There are ominous drums in the background. There is a ship to your east with a gangplank to the shore";
	rooms[ISLAND].shortd = "You are at the island";
	rooms[ISLAND].direction.north = NOROOM;
	rooms[ISLAND].direction.south = NOROOM;
	rooms[ISLAND].direction.west = TREE;
	rooms[ISLAND].direction.east = GANGPLANK;
	rooms[ISLAND].direction.up = NOROOM;
	rooms[ISLAND].direction.down = NOROOM;
	rooms[ISLAND].returning = false;

	rooms[GANGPLANK].longd = "You are aboard the Gangplank. The ocean surrounds you. To your east is the entrance to the ship's upperdeck.";
	rooms[GANGPLANK].shortd = "You are on the GangPlank.";
	rooms[GANGPLANK].direction.north = NOROOM;
	rooms[GANGPLANK].direction.south = NOROOM;
	rooms[GANGPLANK].direction.west = ISLAND;
	rooms[GANGPLANK].direction.east = UPPERDECK;
	rooms[GANGPLANK].direction.up = NOROOM;
	rooms[GANGPLANK].direction.down = NOROOM;
	rooms[GANGPLANK].returning = false;

	rooms[SHIPWHEEL].longd = "If the gorilla is there: There is a large gorilla by the ship's wheel. This gorilla is hostile. You can't approach the wheel. If the gorilla is not there: You are at the wheel.";
	rooms[SHIPWHEEL].shortd = "You are at the ship's wheel";
	rooms[SHIPWHEEL].direction.north = NOROOM;
	rooms[SHIPWHEEL].direction.south = UPPERDECK;
	rooms[SHIPWHEEL].direction.west = NOROOM;
	rooms[SHIPWHEEL].direction.east = NOROOM;
	rooms[SHIPWHEEL].direction.up = NOROOM;
	rooms[SHIPWHEEL].direction.down = NOROOM;
	rooms[SHIPWHEEL].returning = false;

	rooms[UPPERDECK].longd = "The top deck has a wheel at the north end of the ship, and the south end of the ship has a ladder down to the lower deck. ";
	rooms[UPPERDECK].shortd = "You are at the upperdeck";
	rooms[UPPERDECK].direction.north = SHIPWHEEL;
	rooms[UPPERDECK].direction.south = CAPTAINQUARTERS;
	rooms[UPPERDECK].direction.west = GANGPLANK;
	rooms[UPPERDECK].direction.east = NOROOM;
	rooms[UPPERDECK].direction.up = NOROOM;
	rooms[UPPERDECK].direction.down = BOTTOMDECK;
	rooms[UPPERDECK].returning = false;

	rooms[BOTTOMDECK].longd = "The deck below is dimly lit, and smells musty. You can make out three doors. One is to the east, one is to the west, and one is a trapdoor below you.";
	rooms[BOTTOMDECK].shortd = "You are at the bottomdeck";
	rooms[BOTTOMDECK].direction.north = NOROOM;
	rooms[BOTTOMDECK].direction.south = NOROOM;
	rooms[BOTTOMDECK].direction.west = CARGOHOLD;
	rooms[BOTTOMDECK].direction.east = GALLEY;
	rooms[BOTTOMDECK].direction.up = UPPERDECK;
	rooms[BOTTOMDECK].direction.down = BRIG;
	rooms[BOTTOMDECK].returning = false;

	rooms[GALLEY].longd = "This is the galley. It is mostly empty, but in a shadowy corner you see a parrot sitting on a perch.";
	rooms[GALLEY].shortd = "You are at the galley";
	rooms[GALLEY].direction.north = NOROOM;
	rooms[GALLEY].direction.south = NOROOM;
	rooms[GALLEY].direction.west = BOTTOMDECK;
	rooms[GALLEY].direction.east = NOROOM;
	rooms[GALLEY].direction.up = NOROOM;
	rooms[GALLEY].direction.down = NOROOM;
	rooms[GALLEY].returning = false;

	rooms[BRIG].longd = "In this room there is a prisoner in a locked cell. He says,'Jack, I'm so glad you're alive. The captain locked me up for cheating at cards, which is the only reason the islanders didn't capture me. They killed everyone else. Now I guess we're the only two left, which makes you captain since you were first mate. Go find the keys to unlock this door, and we can sail out of here.'";
	rooms[BRIG].shortd = "You are at the brig";
	rooms[BRIG].direction.north = NOROOM;
	rooms[BRIG].direction.south = NOROOM;
	rooms[BRIG].direction.west = NOROOM;
	rooms[BRIG].direction.east = NOROOM;
	rooms[BRIG].direction.up = CARGOHOLD;
	rooms[BRIG].direction.down = NOROOM;
	rooms[BRIG].returning = false;

	rooms[CAPTAINQUARTERS].longd = "There is a bed and a table in this room.";
	rooms[CAPTAINQUARTERS].shortd = "You are at the captain's quarters";
	rooms[CAPTAINQUARTERS].direction.north = UPPERDECK;
	rooms[CAPTAINQUARTERS].direction.south = NOROOM;
	rooms[CAPTAINQUARTERS].direction.west = NOROOM;
	rooms[CAPTAINQUARTERS].direction.east = NOROOM;
	rooms[CAPTAINQUARTERS].direction.up = NOROOM;
	rooms[CAPTAINQUARTERS].direction.down = NOROOM;
	rooms[CAPTAINQUARTERS].returning = false;

	rooms[CARGOHOLD].longd = "You've entered the cargo hold. There are barrels, a pile of tools, and a trunk. (Treasure is in the trunk.)";
	rooms[CARGOHOLD].shortd = "You are at the cargohold";
	rooms[CARGOHOLD].direction.north = NOROOM;
	rooms[CARGOHOLD].direction.south = NOROOM;
	rooms[CARGOHOLD].direction.east = BOTTOMDECK;
	rooms[CARGOHOLD].direction.west = NOROOM;
	rooms[CARGOHOLD].direction.up = NOROOM;
	rooms[CARGOHOLD].direction.down = NOROOM;
	rooms[CARGOHOLD].returning = false;

}
