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
const string Vend = "yay";
const string Cend = "ay";

//Eventually possibly include "Ocean" to rooms
enum rooms { TREE, ISLAND, GANGPLANK, UPPERDECK, SHIPWHEEL, BOTTOMDECK, GALLEY, BRIG, CAPTAINQUARTERS, CARGOHOLD, LADDER, GCAVE, NOROOM };

struct itemlist {
	bool knife;
	bool banana;
	bool treasure;
	bool keys;
};
struct puzzle {
	bool knife;
	bool gorilla;
	bool prisoner;
	bool parrot;
	bool natives;
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

struct inventory {
	itemlist item;
};


void initialize(roomType[]);    // Has to be roomtype[NOROOM] for some reason

void execute(string&, rooms&, rooms&, roomType[], inventory&, puzzle&, int&, ofstream&); // rooms has an & next to it because we need the function to return the current room

void parrot(string[], int);//PigLatin

int check(string);//PigLatin

string piglatin(string);//PigLatin

int VowelFind(string);//PigLatin

bool pwordcheck(string[]);

void invent(inventory);

void initializeStatus(roomType[], rooms&, inventory&, puzzle&);

void loadGame(ifstream&, inventory&, rooms&, roomType[], puzzle&);

void saveGame(ofstream&, inventory, rooms, roomType[], puzzle);

char EnumToChar(rooms);

void itemDisplay(puzzle, rooms, roomType[]);

int puzcounter(puzzle);

int roomcounter(roomType[]);

//------------------------------------------------------------------------------------------------------------------------------------------

int main()
{
	ofstream Save;
	ifstream Load("SaveFile.txt");
	inventory inv;
	puzzle puz;
	int gameCheck, turncount, score, puzzlescore, roomscore, turnscore;
	gameCheck = 0;
	string command;
	string start;
	roomType room[NOROOM];
	rooms currentRoom, lastRoom;
	command = "empty";
	char LoadAnswer;
	initialize(room);                        // initialize sets everything up from the start of the game
	currentRoom = ISLAND;
	bool gameOver = false;
	int tell;
	tell = 0;
	turncount = 0;

	if (Load.is_open())
	{
		cout << "A saved game exists. Would you like to load this?" << endl;
		LoadAnswer = cin.get();
		cin.ignore(999, '\n');
		if (tolower(LoadAnswer) == 'y' or tolower(LoadAnswer) == 'l')
		{
			cout << "DATA LOADED" << endl;
			loadGame(Load, inv, currentRoom, room, puz);
		}
		else
			initializeStatus(room, currentRoom, inv, puz);    //  RESTART
	}
	else
		initializeStatus(room, currentRoom, inv, puz);    // NEW GAME 



	lastRoom = currentRoom;

	gameOver = command == "quit";
	while (not gameOver)
	{
		if (room[currentRoom].returning)
		{
			cout << room[currentRoom].shortd << endl << endl;    // Always prints short description
			itemDisplay(puz, currentRoom, room);

			if (currentRoom == SHIPWHEEL and !puz.gorilla)
			{
				cout << "You are near the ship's wheel" << endl;
			}
			else
			{
				if (currentRoom == SHIPWHEEL and puz.gorilla)
				{
					cout << "You are at the ship's wheel" << endl;
				}
			}
		}
		else     // player has never been in this room before
		{
			cout << room[currentRoom].longd << endl << endl;
			itemDisplay(puz, currentRoom, room);

			if (currentRoom == SHIPWHEEL and !puz.gorilla)
			{
				cout << "You are near the wheel" << endl;
			}
			else
			{
				if (currentRoom == SHIPWHEEL and puz.gorilla)
				{
					cout << "You are at the wheel" << endl;
				}
			}
		}



		getline(cin, command);
		tell++;


		execute(command, currentRoom, lastRoom, room, inv, puz, gameCheck, Save);
		// First send command. Then currentRoom. Then lastRoom. Then send room information. Then send player inventory. Then puzzle status. Lastly Save file. 



		if (currentRoom == NOROOM)    // NOROOM is used when you cannot go into an area
		{
			cout << "You can't go that way" << endl;
			currentRoom = lastRoom;  //Sets current room to whatever room you were in before
		}
		if (gameCheck == 1)
		{
			command = "quit";
		}
		//lastRoom = currentRoom;
		//cout << "Last room " << lastRoom << endl;
		gameOver = command == "quit";

	}
	score = 0;
	//31 11 5
	//660 230 110
	turnsperfcore = tell * 1000;
	puzzleperfscore = (puzcounter(puz)) * 50000;
	roomperfscore = (roomcounter(room)) * 10000;
	score = score - puzzlescore - roomscore - turnscore;

	if (gameCheck == 1)
	{
		cout << "---------------------------------" << endl;
		cout << "You won! Congratulations" << endl;
		cout << "---------------------------------" << endl;
		cout << "Puzzles completed : " << puzcounter(puz) << " out of 5 puzzles completed" << endl;
		cout << "Areas found : " << roomcounter(room) - 1 << " out of 11 areas found" << endl;
		cout << "Turns taken : " << tell << endl;
		cout << "Score : " << score << endl;
	}
	else
	{
		cout << "---------------------------------" << endl;
		cout << "GAME OVER" << endl;
		cout << "---------------------------------" << endl;
		cout << "Puzzles completed : " << puzcounter(puz) << " out of 5 puzzles completed" << endl;
		cout << "Areas found : " << roomcounter(room) - 1 << " out of 11 areas found" << endl;
		cout << "Turns taken : " << tell - 1 << endl;
		if (score < 0)
		{
			cout << "Score : 0" << endl;
		}
		else
		{
			cout << "Score : " << score << endl;
		}
	}
	return 0;
}

int puzcounter(puzzle puz)
{
	int count;
	count = 0;
	if (puz.gorilla)
	{
		count++;
	}
	if (puz.knife)
	{
		count++;
	}
	if (puz.natives)
	{
		count++;
	}
	if (puz.parrot)
	{
		count++;
	}
	if (puz.prisoner)
	{
		count++;
	}

	return count;
}

int roomcounter(roomType rooms[NOROOM])
{
	int i, count;
	count = 0;
	for (i = 0; i <= NOROOM - 1; i++)
	{
		if (rooms[i].returning)
		{
			count++;
		}
	}
	return count;
}

void loadGame(ifstream& load, inventory& inv, rooms& current, roomType rooms[NOROOM], puzzle& puz)
{

	char line[200];
	int place = 0;
	int i = 0;
	while (!load.eof())
	{
		line[i] = load.get();
		load.ignore(256, '\n');
		i++;
	}

	for (i = 0; i <= NOROOM - 1; i++)
	{
		if (line[place] == 'T')
			rooms[i].item.banana = true;
		else
			rooms[i].item.banana = false;
		place++;

		if (line[place] == 'T')
			rooms[i].item.knife = true;
		else
			rooms[i].item.knife = false;
		place++;

		if (line[place] == 'T')
			rooms[i].item.treasure = true;
		else
			rooms[i].item.treasure = false;
		place++;

		if (line[place] == 'T')
			rooms[i].item.keys = true;
		else
			rooms[i].item.keys = false;
		place++;

		if (line[place] == 'T')
			rooms[i].returning = true;
		else
			rooms[i].returning = false;
		place++;
	}


	if (line[place] == 'T')
		inv.item.banana = true;
	else
		inv.item.banana = false;
	place++;

	if (line[place] == 'T')
		inv.item.knife = true;
	else
		inv.item.knife = false;
	place++;

	if (line[place] == 'T')
		inv.item.treasure = true;
	else
		inv.item.treasure = false;
	place++;
	if (line[place] == 'T')
		inv.item.keys = true;
	else
		inv.item.keys = false;
	place++;


	if (line[place] == 'T')
		puz.gorilla = true;
	else
		puz.gorilla = false;
	place++;
	if (line[place] == 'T')
		puz.prisoner = true;
	else
		puz.prisoner = false;
	place++;
	if (line[place] == 'T')
		puz.natives = true;
	else
		puz.natives = false;
	place++;
	if (line[place] == 'T')
		puz.parrot = true;
	else
		puz.parrot = true;
	place++;
	switch (line[place])     // SETS CURRENT ROOM
	{
	case 'a': current = TREE; break;
	case 'b': current = ISLAND; break;
	case 'c': current = GANGPLANK; break;
	case 'd': current = UPPERDECK; break;
	case 'e': current = SHIPWHEEL; break;
	case 'f': current = BOTTOMDECK; break;
	case 'g': current = GALLEY; break;
	case 'h': current = BRIG; break;
	case 'i': current = CAPTAINQUARTERS; break;
	case 'j': current = CARGOHOLD; break;
	case 'k': current = LADDER; break;
	case 'l': current = GCAVE; break;
	default: current = ISLAND;
	}

}



void saveGame(ofstream& Save, inventory inv, rooms current, roomType rooms[NOROOM], puzzle puz)    /// This is the save feature 
{
	Save.open("SaveFile.txt");
	int i;

	for (i = 0; i <= NOROOM - 1; i++)    // Cycles the number of rooms and checks if items are in that room and prints true or false
	{
		if (rooms[i].item.banana)
			Save << "TRUE banana for room " << i << endl;
		else
			Save << "FALSE banana for room " << i << endl;

		if (rooms[i].item.knife)
			Save << "TRUE knife for room " << i << endl;
		else
			Save << "FALSE knife for room " << i << endl;

		if (rooms[i].item.treasure)
			Save << "TRUE treasure for room " << i << endl;
		else
			Save << "FALSE treasure for room " << i << endl;

		if (rooms[i].item.keys)
			Save << "TRUE keys for room " << i << endl;
		else
			Save << "FALSE keys for room " << i << endl;

		if (rooms[i].returning)
			Save << "TRUE returning for room " << i << endl;
		else
			Save << "FALSE returning for room " << i << endl;
	}


	if (inv.item.banana)     // This checks the inventory of the player
	{
		Save << "TRUE banana for inventory " << endl;
	}
	else
	{
		Save << "FALSE banana for inventory " << endl;
	}
	if (inv.item.knife)
	{
		Save << "TRUE knife for inventory " << endl;
	}
	else
	{
		Save << "FALSE knife for inventory " << endl;
	}
	if (inv.item.treasure)
	{
		Save << "TRUE treasure for inventory " << endl;
	}
	else
	{
		Save << "FALSE treasure for inventory " << endl;
	}
	if (inv.item.keys)
	{
		Save << "TRUE keys for inventory " << endl;
	}
	else
	{
		Save << "FALSE keys for inventory " << endl;
	}


	if (puz.gorilla)    // PUZZLE STATUS
	{
		Save << "TRUE gorilla" << endl;
	}
	else
	{
		Save << "FALSE gorilla" << endl;
	}
	if (puz.prisoner)
	{
		Save << "TRUE prisoner" << endl;
	}
	else
	{
		Save << "FALSE prisoner" << endl;
	}
	if (puz.natives)
	{
		Save << "TRUE natives" << endl;
	}
	else
	{
		Save << "FALSE natives" << endl;
	}
	if (puz.parrot)
	{
		Save << "TRUE parrot" << endl;
	}
	else
	{
		Save << "FALSE parrot" << endl;
	}

	Save << EnumToChar(current) << endl;  // This keeps track of the current location of the player. It will print a number 

	cout << endl;
	cout << "...Saving..." << endl;
	cout << "You saved the game!" << endl;
	cout << endl;

}



void initialize(roomType rooms[NOROOM])
{

	rooms[TREE].longd = "There is a large banana tree here. (There is one bunch of ripe bananas on the tree within reach.)";
	rooms[TREE].shortd = "You are at the tree. (There is one bunch of ripe bananas on the tree within reach.)";
	rooms[TREE].direction.north = NOROOM;
	rooms[TREE].direction.south = NOROOM;
	rooms[TREE].direction.west = NOROOM;
	rooms[TREE].direction.east = ISLAND;
	rooms[TREE].direction.up = NOROOM;
	rooms[TREE].direction.down = NOROOM;

	rooms[ISLAND].longd = "The island is forested with banana trees. Most of the bananas are green, but one tree to your west might have ripe bananas. There are ominous drums in the background. There is a ship to your east with a gangplank to the shore";
	rooms[ISLAND].shortd = "You are at the island";
	rooms[ISLAND].direction.north = NOROOM;
	rooms[ISLAND].direction.south = NOROOM;
	rooms[ISLAND].direction.west = TREE;
	rooms[ISLAND].direction.east = GANGPLANK;
	rooms[ISLAND].direction.up = NOROOM;
	rooms[ISLAND].direction.down = NOROOM;

	rooms[GANGPLANK].longd = "You are aboard the Gangplank. The ocean surrounds you. To your east is the entrance to the ship's upperdeck.";
	rooms[GANGPLANK].shortd = "You are on the GangPlank.";
	rooms[GANGPLANK].direction.north = NOROOM;
	rooms[GANGPLANK].direction.south = NOROOM;
	rooms[GANGPLANK].direction.west = ISLAND;
	rooms[GANGPLANK].direction.east = UPPERDECK;
	rooms[GANGPLANK].direction.up = NOROOM;
	rooms[GANGPLANK].direction.down = NOROOM;

	rooms[SHIPWHEEL].longd = "";
	rooms[SHIPWHEEL].shortd = "";
	rooms[SHIPWHEEL].direction.north = NOROOM;
	rooms[SHIPWHEEL].direction.south = UPPERDECK;
	rooms[SHIPWHEEL].direction.west = NOROOM;
	rooms[SHIPWHEEL].direction.east = NOROOM;
	rooms[SHIPWHEEL].direction.up = NOROOM;
	rooms[SHIPWHEEL].direction.down = NOROOM;

	rooms[UPPERDECK].longd = "You are on the uppderdeck which has a wheel to the north end of the ship, the gangplank to west, and to the south there is a ladder down to the lower deck. ";
	rooms[UPPERDECK].shortd = "You are at the upperdeck";
	rooms[UPPERDECK].direction.north = SHIPWHEEL;
	rooms[UPPERDECK].direction.south = LADDER;
	rooms[UPPERDECK].direction.west = GANGPLANK;
	rooms[UPPERDECK].direction.east = NOROOM;
	rooms[UPPERDECK].direction.up = NOROOM;
	rooms[UPPERDECK].direction.down = BOTTOMDECK;

	rooms[BOTTOMDECK].longd = "The deck below is dimly lit, and smells musty. You can make out three doors. One is to the east, one is to the west, and one is a trapdoor below you.";
	rooms[BOTTOMDECK].shortd = "You are at the bottomdeck";
	rooms[BOTTOMDECK].direction.north = NOROOM;
	rooms[BOTTOMDECK].direction.south = NOROOM;
	rooms[BOTTOMDECK].direction.west = CARGOHOLD;
	rooms[BOTTOMDECK].direction.east = GALLEY;
	rooms[BOTTOMDECK].direction.up = LADDER;
	rooms[BOTTOMDECK].direction.down = BRIG;

	rooms[GALLEY].longd = "This is the galley. It is mostly empty, but in a shadowy corner you see a parrot sitting on a perch.";
	rooms[GALLEY].shortd = "You are at the galley";
	rooms[GALLEY].direction.north = NOROOM;
	rooms[GALLEY].direction.south = NOROOM;
	rooms[GALLEY].direction.west = BOTTOMDECK;
	rooms[GALLEY].direction.east = NOROOM;
	rooms[GALLEY].direction.up = NOROOM;
	rooms[GALLEY].direction.down = NOROOM;

	rooms[BRIG].longd = "You are in the brig  and in this room there is a prisoner in a locked cell. He says,'Jack, I'm so glad you're alive. The captain locked me up for cheating at cards, which is the only reason the islanders didn't capture me. They killed everyone else. Now I guess we're the only two left, which makes you captain since you were first mate. Go find the keys to unlock this door, and we can sail out of here.'";
	rooms[BRIG].shortd = "You are at the brig";
	rooms[BRIG].direction.north = NOROOM;
	rooms[BRIG].direction.south = NOROOM;
	rooms[BRIG].direction.west = NOROOM;
	rooms[BRIG].direction.east = NOROOM;
	rooms[BRIG].direction.up = BOTTOMDECK;
	rooms[BRIG].direction.down = NOROOM;

	rooms[CAPTAINQUARTERS].longd = "You at the captain's quarters which contains a bed and a table.";
	rooms[CAPTAINQUARTERS].shortd = "You are at the captain's quarters";
	rooms[CAPTAINQUARTERS].direction.north = LADDER;
	rooms[CAPTAINQUARTERS].direction.south = NOROOM;
	rooms[CAPTAINQUARTERS].direction.west = NOROOM;
	rooms[CAPTAINQUARTERS].direction.east = NOROOM;
	rooms[CAPTAINQUARTERS].direction.up = NOROOM;
	rooms[CAPTAINQUARTERS].direction.down = NOROOM;

	rooms[CARGOHOLD].longd = "You've entered the cargo hold. There are barrels, a pile of tools, and a trunk.";
	rooms[CARGOHOLD].shortd = "You are at the cargohold";
	rooms[CARGOHOLD].direction.north = NOROOM;
	rooms[CARGOHOLD].direction.south = NOROOM;
	rooms[CARGOHOLD].direction.east = BOTTOMDECK;
	rooms[CARGOHOLD].direction.west = NOROOM;
	rooms[CARGOHOLD].direction.up = NOROOM;
	rooms[CARGOHOLD].direction.down = NOROOM;

	rooms[LADDER].longd = "You're above the ladder on the upper deck. South of you is the Captain's Quarters. Below you is the lower deck. North of you is the ship' wheel.   ";
	rooms[LADDER].shortd = " You're near the ladder on the upper deck. ";
	rooms[LADDER].direction.north = UPPERDECK;
	rooms[LADDER].direction.south = CAPTAINQUARTERS;
	rooms[LADDER].direction.east = NOROOM;
	rooms[LADDER].direction.west = NOROOM;
	rooms[LADDER].direction.up = GCAVE;
	rooms[LADDER].direction.down = BOTTOMDECK;


	//Custom
	rooms[GCAVE].longd = "Welcome to the 'God Cave' where everything is free to take :)";
	rooms[GCAVE].shortd = " How is it going? The 'God Cave' welcomes you. ";
	rooms[GCAVE].direction.north = GCAVE;
	rooms[GCAVE].direction.south = GCAVE;
	rooms[GCAVE].direction.east = GCAVE;
	rooms[GCAVE].direction.west = GCAVE;
	rooms[GCAVE].direction.up = GCAVE;
	rooms[GCAVE].direction.down = LADDER;
	//Custom
}

void parrot(string word[], int count)//Remove check
{
	int i;
	i = 0;
	while (i <= count - 1)
	{
		cout << piglatin(word[i]) << " ";
		i++;
	}
	cout << endl;
	//cout << piglatin(word[0]) << " " << piglatin(word[1]) << " " << endl;
}

void invent(inventory inv)
{
	if (inv.item.banana)
	{
		cout << "Banana" << endl;
	}
	if (inv.item.keys)
	{
		cout << "Keys" << endl;
	}
	if (inv.item.knife)
	{
		cout << "Knife" << endl;
	}
	if (inv.item.treasure)
	{
		cout << "Treasure" << endl;
	}
}

string piglatin(string word)
{
	int firstvowel;
	string begword, newword;
	firstvowel = VowelFind(word);
	if (firstvowel != 0)
	{
		begword = word.substr(0, firstvowel);
		word = word.erase(0, firstvowel);
		newword = word + begword + Cend;
		return newword;
	}
	else {
		newword = word + Vend;
		return newword;
	}

}

int VowelFind(string thing)
{
	int vow[6], fv, i;
	int outer, temp, count;
	outer = 6;
	temp = 0;
	count = 6;
	i = 0;
	if (thing.find('a') >= 0)
	{
		vow[0] = thing.find('a');
	}
	if (thing.find('e') >= 0)
	{
		vow[1] = thing.find('e');
	}
	if (thing.find('i') >= 0)
	{
		vow[2] = thing.find('i');
	}
	if (thing.find('o') >= 0)
	{
		vow[3] = thing.find('o');
	}
	if (thing.find('u') >= 0)
	{
		vow[4] = thing.find('u');
	}
	if (thing.find('y') >= 0)
	{
		vow[5] = thing.find('y');
	}
	for (outer = outer - 1; outer > 0; outer--)
	{
		for (i = 0; i < count - 1; i++)
		{
			if (vow[i] > vow[i + 1] and vow[i] >= 0)
			{
				temp = vow[i];
				vow[i] = vow[i + 1];
				vow[i + 1] = temp;
			}
		}
	}
	i = 0;
	while (i <= 5)
	{
		if (vow[i] >= 0)
		{
			fv = vow[i];
			i = 5;
		}
		i++;
	}
	return fv;
}

bool pwordcheck(string pword[])
{
	int i;
	bool check;
	check = false;
	i = 0;
	while (not check and i <= 5)
	{
		if (pword[i] == "hello" or pword[i] == "polly" or pword[i] == "cracker")
		{
			check = true;
		}
		else
		{
			i++;
		}
	}
	return check;
}

void itemDisplay(puzzle puz, rooms currentRoom, roomType rooms[NOROOM])
{
	if (rooms[currentRoom].item.banana and currentRoom != TREE)
	{
		cout << "(There are bananas on the ground)" << endl;
	}
	if (rooms[currentRoom].item.keys)
	{
		if (currentRoom == CAPTAINQUARTERS and puz.parrot)
		{
			cout << "(There are keys in the secret compartment)" << endl;
		}
		else
		{
			if (currentRoom == CAPTAINQUARTERS and !puz.parrot)
			{

			}
			else
			{
				cout << "(There are keys on the ground)" << endl;
			}
		}
	}
	if (rooms[currentRoom].item.knife)
	{
		cout << "(There is a knife on the ground)" << endl;
	}
	if (rooms[currentRoom].item.treasure)
	{
		cout << "(There is treasure)" << endl;
	}
}







void initializeStatus(roomType RoomStatus[NOROOM], rooms& current, inventory& inv, puzzle& puz)   // This function only occurs if there is no save game. So basically this is the start of the game.
{
	cout << "---------------------------------------------------------" << endl;
	cout << endl << endl;
	cout << "Welcome to Adventure Island!" << endl << endl;
	cout << "You have just awakened on a strange island with a terrible headache." << endl;
	cout << "You can't remember anything about yourself or where you are." << endl;
	cout << "You need to overcome a series of obstacles in order to be able to board a pirate ship and sail it to civilization" << endl;
	cout << "Type 'help' at any time to view instructions" << endl << endl;
	cout << "Good luck and have fun!" << endl;
	cout << endl;

	current = ISLAND;

	puz.knife = false;
	puz.gorilla = false;
	puz.natives = false;
	puz.parrot = false;
	puz.prisoner = false;

	inv.item.keys = false;
	inv.item.treasure = false;
	inv.item.knife = false;
	inv.item.banana = false;

	RoomStatus[GCAVE].returning = true;
	RoomStatus[GCAVE].item.knife = true;
	RoomStatus[GCAVE].item.banana = true;
	RoomStatus[GCAVE].item.treasure = true;
	RoomStatus[GCAVE].item.keys = true;

	RoomStatus[LADDER].returning = false;
	RoomStatus[LADDER].item.knife = false;
	RoomStatus[LADDER].item.banana = false;
	RoomStatus[LADDER].item.treasure = false;
	RoomStatus[LADDER].item.keys = false;

	RoomStatus[TREE].returning = false;
	RoomStatus[TREE].item.knife = false;
	RoomStatus[TREE].item.banana = true;
	RoomStatus[TREE].item.treasure = false;
	RoomStatus[TREE].item.keys = false;

	RoomStatus[ISLAND].returning = false;
	RoomStatus[ISLAND].item.knife = false;
	RoomStatus[ISLAND].item.banana = false;
	RoomStatus[ISLAND].item.treasure = false;
	RoomStatus[ISLAND].item.keys = false;

	RoomStatus[GANGPLANK].returning = false;
	RoomStatus[GANGPLANK].item.knife = false;
	RoomStatus[GANGPLANK].item.banana = false;
	RoomStatus[GANGPLANK].item.treasure = false;
	RoomStatus[GANGPLANK].item.keys = false;

	RoomStatus[SHIPWHEEL].returning = false;
	RoomStatus[SHIPWHEEL].item.knife = false;
	RoomStatus[SHIPWHEEL].item.banana = false;
	RoomStatus[SHIPWHEEL].item.treasure = false;
	RoomStatus[SHIPWHEEL].item.keys = false;

	RoomStatus[UPPERDECK].returning = false;
	RoomStatus[UPPERDECK].item.knife = false;
	RoomStatus[UPPERDECK].item.banana = false;
	RoomStatus[UPPERDECK].item.treasure = false;
	RoomStatus[UPPERDECK].item.keys = false;

	RoomStatus[BOTTOMDECK].returning = false;
	RoomStatus[BOTTOMDECK].item.knife = false;
	RoomStatus[BOTTOMDECK].item.banana = false;
	RoomStatus[BOTTOMDECK].item.treasure = false;
	RoomStatus[BOTTOMDECK].item.keys = false;

	RoomStatus[GALLEY].returning = false;
	RoomStatus[GALLEY].item.knife = false;
	RoomStatus[GALLEY].item.banana = false;
	RoomStatus[GALLEY].item.treasure = false;
	RoomStatus[GALLEY].item.keys = false;

	RoomStatus[BRIG].returning = false;
	RoomStatus[BRIG].item.knife = false;
	RoomStatus[BRIG].item.banana = false;
	RoomStatus[BRIG].item.treasure = false;
	RoomStatus[BRIG].item.keys = false;

	RoomStatus[CAPTAINQUARTERS].returning = false;
	RoomStatus[CAPTAINQUARTERS].item.knife = true;
	RoomStatus[CAPTAINQUARTERS].item.banana = false;
	RoomStatus[CAPTAINQUARTERS].item.treasure = false;
	RoomStatus[CAPTAINQUARTERS].item.keys = true;

	RoomStatus[CARGOHOLD].returning = false;
	RoomStatus[CARGOHOLD].item.knife = false;
	RoomStatus[CARGOHOLD].item.banana = false;
	RoomStatus[CARGOHOLD].item.treasure = true;
	RoomStatus[CARGOHOLD].item.keys = false;
}








void execute(string& command, rooms& currentRoom, rooms& lastRoom, roomType rooms[NOROOM], inventory& inv, puzzle& puz, int& gameCheck, ofstream& Save)
{

	string word[2], pword[15];
	int blank, i;
	string pcommand;
	bool pcheck;

	command = command + " ";
	i = 0;
	while (command != "" and i <= 1)
	{
		if (command != "")
		{
			blank = command.find(' ');
			word[i] = command.substr(0, blank);
			command = command.erase(0, blank + 1);
		}
		i++;
	}

	cout << endl;

	if (word[0] == "south" or word[0] == "s" or word[1] == "south" or word[1] == "s")
	{
		lastRoom = currentRoom;
		currentRoom = rooms[currentRoom].direction.south;
	}
	else if (word[0] == "east" or word[0] == "e" or word[1] == "east" or word[1] == "e")
	{
		lastRoom = currentRoom;
		currentRoom = rooms[currentRoom].direction.east;
	}
	else if (word[0] == "west" or word[0] == "w" or word[1] == "west" or word[1] == "w")
	{
		lastRoom = currentRoom;
		currentRoom = rooms[currentRoom].direction.west;
	}
	else if (word[0] == "north" or word[0] == "n" or word[1] == "north" or word[1] == "n")
	{
		lastRoom = currentRoom;
		currentRoom = rooms[currentRoom].direction.north;
	}
	else if (word[0] == "up" or word[0] == "u" or word[1] == "up" or word[1] == "u")
	{
		lastRoom = currentRoom;
		currentRoom = rooms[currentRoom].direction.up;
	}
	else if (word[0] == "down" or word[0] == "d" or word[1] == "down" or word[1] == "d")
	{
		lastRoom = currentRoom;
		currentRoom = rooms[currentRoom].direction.down;
	}


	else if (word[0] == "take" or word[0] == "grab" or word[0] == "pickup" or word[0] == "get")    // PICK UP STUFF
	{
		if (word[1] == "keys" or word[1] == "key")
		{
			if (rooms[currentRoom].item.keys)
			{
				if (puz.parrot or currentRoom == GCAVE)
				{
					if (rooms[currentRoom].item.keys)
					{
						rooms[currentRoom].item.keys = false;
						inv.item.keys = true;
						cout << "You got the keys!" << endl;
					}
					else
						cout << "No keys here bucko." << endl;
				}
				else
				{
					cout << "No keys here bucko." << endl;
				}
			}
			else
			{
				cout << "No keys here bucko." << endl;
			}
		}


		else if (word[1] == "banana" or word[1] == "bananas")
		{
			if (rooms[currentRoom].item.banana)
			{
				if (currentRoom != TREE)
				{
					inv.item.banana = true;
					rooms[currentRoom].item.banana = false;
					cout << "You picked up a banana." << endl;
				}
				else if (inv.item.knife)
				{
					inv.item.banana = true;
					cout << "You cut down a banana!" << endl;
					puz.knife = true;
					cout << " /`-.__                                 /\\" << endl;
					cout << " `. .  ~~--..__                   __..-' ,'" << endl;
					cout << "   `.`-.._     ~~---...___...---~~  _,~,/" << endl;
					cout << "     `-._ ~--..__             __..-~ _-~" << endl;
					cout << "         ~~-..__ ~~--.....--~~   _.-~" << endl;
					cout << "                ~~--...___...--~~" << endl;
					cout << endl;
				}
				else
					cout << "You'll need a knife to cut these down." << endl;
			}
			else
				cout << "There are no bananas here." << endl;
		}


		else if (word[1] == "knife" or word[1] == "blade")
		{
			if (rooms[currentRoom].item.knife)
			{
				rooms[currentRoom].item.knife = false;
				inv.item.knife = true;
				cout << "You picked up a knife!" << endl;
				cout << endl;
				cout << "                                  _____________________________" << endl;
				cout << "                           _.-''``------------------------|`. |``''--..__" << endl;
				cout << "                      _.-'` ' ' ' ' ' ' ' ' ' ' ' ' ' ' ' | : |          ``'';';--..__" << endl;
				cout << "                 _.-'`                                    | : |         '   :';       ```';" << endl;
				cout << "            _.-'`                           ________/\_/\_|.'_|_       '   :';           /" << endl;
				cout << "       _.-'`                         _.-''``                    ``''--:.__;';           _|" << endl;
				cout << "     .'`                        _.-'`                                     `'`''-._     /" << endl;
				cout << "   .`                       _.-'                                                  `'-./" << endl;
				cout << " .'                    _.-'`" << endl;
				cout << "/               __..-'`" << endl;
				cout << "``'''----'''````" << endl;
			}
			else
				cout << "There is no knife here!" << endl;
		}
		else if (word[1] == "treasure")
		{
			if (rooms[currentRoom].item.treasure)
			{
				rooms[currentRoom].item.treasure = false;
				inv.item.treasure = true;
				cout << "You take the treasure!" << endl;
			}
		}
		else
		{
			cout << "Invalid command. Type 'help' to see commands." << endl;
		}
	}

	else if (word[0] == "eat" and word[1] == "banana" or word[0] == "eat" and word[1] == "banana")
	{
		if (inv.item.banana)
		{
			cout << "chomp chomp chomp" << endl;
			cout << "..." << endl;
			cout << "You ate the banana!" << endl;
			inv.item.banana = false;
		}
		else
		{
			cout << "You don't have that item." << endl;
		}
	}

	else if (word[0] == "use")
	{
		if (word[1] == "knife")
		{
			if (currentRoom == TREE and inv.item.knife)
			{
				cout << "You cut down a banana!" << endl;
				inv.item.banana = true;
				puz.knife = true;
			}
		}
		else if (word[1] == "wheel")
		{
			if (!puz.gorilla)
			{
				cout << "The gorilla roars at you, you whimper away in fear" << endl;
			}
		}

		else if (word[1] == "keys")
		{

		}
		else
		{
			cout << "Invalid command. Type 'help' to see commands." << endl;
		}
	}


	else if (word[0] == "drop" or word[0] == "place")    // DROP STUFF
	{
		if (word[1] == "keys" or word[1] == "key")
		{
			if (inv.item.keys)
			{
				inv.item.keys = false;
				rooms[currentRoom].item.keys = true;
				cout << "You dropped the keys" << endl;
			}
			else
				cout << "You dont have the keys" << endl;
		}
		else if (word[1] == "knife")
		{
			if (inv.item.knife)
			{
				inv.item.knife = false;
				rooms[currentRoom].item.knife = true;
				cout << "You placed the knife" << endl;
			}
			else
				cout << "You don't have this item!" << endl;
		}
		else if (word[1] == "treasure")
		{
			if (inv.item.treasure)
			{
				inv.item.treasure = false;
				rooms[currentRoom].item.treasure = true;
				cout << "You placed down the treasure." << endl;
			}
			else
				cout << "You don't have that item" << endl;
		}
		else if (word[1] == "banana" or word[1] == "bananas")
		{
			if (inv.item.banana)
			{
				inv.item.banana = false;
				rooms[currentRoom].item.banana = true;
				cout << "You placed down the banana." << endl;
			}
			else
				cout << "You don't have that item" << endl;
		}
		else
		{
			cout << "Invalid command. Type 'help' to see commands." << endl;
		}
	}
	else if (word[0] == "help")
	{
		cout << "This is a text based game meaning you will have to enter commands in order" << endl;
		cout << "to control your character" << endl;
		cout << "You can input up to two words to use as actions." << endl;
		cout << "For example : 'go west', 'west', or simply 'w' will take you west." << endl;
		cout << "Commands such as 'pickup', 'take', 'grab', or 'get' will place an item into your inventory." << endl;
		cout << "Inputting 'inventory' will show you your current items." << endl;
		cout << "You can type 'look' to recieve a longer description of where you are at." << endl;
		cout << "Typing 'commands' will show most basic commands" << endl;
		cout << "Typing 'save' will save your progress" << endl;
		cout << endl << endl;
	}
	else if (word[0] == "commands")
	{
		cout << " - = - = Movement = - = -" << endl;
		cout << "West || 'go west' 'west' 'w'" << endl;
		cout << "East || 'go east' 'east' 'e'" << endl;
		cout << "South || 'go south' 'south' 's'" << endl;
		cout << "North || 'go north' 'north' 'w'" << endl;
		cout << "Up || 'go up' 'up' 'u'" << endl;
		cout << "Down || 'go down' down' 'd'" << endl << endl;

		cout << " - = - = Actions = - = -" << endl;
		cout << "Getting items || 'take -' 'get -'" << endl;
		cout << "Interactions || 'use-' 'drop-' 'eat-'" << endl;
		cout << "Information || 'look' 'inventory' 'help'" << endl << endl;

		cout << " - = - = Game = - = -" << endl;
		cout << "Game || 'quit' 'save' 'restart'" << endl;
	}

	else if (word[0] == "look")
	{
		cout << rooms[currentRoom].longd << endl << endl;
		if (puz.gorilla and currentRoom == SHIPWHEEL)
		{
			cout << "You are at the wheel. To your south is the upper deck" << endl;
		}
		else
		{
			if (!puz.gorilla and currentRoom == SHIPWHEEL)
				cout << "The gorilla blocks your path, you are near the wheel" << endl;
		}
		if (!rooms[currentRoom].item.banana and !rooms[currentRoom].item.keys and !rooms[currentRoom].item.knife
			and !rooms[currentRoom].item.treasure)
		{

		}
		else
		{
			cout << "In this room there are the following :" << endl;
			if (rooms[currentRoom].item.banana)
			{
				cout << "Banana" << endl;
			}
			if (rooms[currentRoom].item.keys)
			{
				if (puz.parrot)
					cout << "Keys" << endl;
			}
			if (rooms[currentRoom].item.knife)
			{
				cout << "Knife" << endl;
			}
			if (rooms[currentRoom].item.treasure)
			{
				cout << "Treasure" << endl;
			}
		}
	}

	else if (word[0] == "inventory")
	{
		cout << "You have :" << endl;
		if (!inv.item.banana and !inv.item.keys and !inv.item.knife and !inv.item.treasure)
		{
			cout << "No items" << endl;
		}
		invent(inv);
	}

	else if (word[0] == "back" or word[0] == "return")
	{
		currentRoom = lastRoom;
	}

	else if (word[0] == "quit")
	{
		command = "quit";
	}

	else if (word[0] == "restart")
	{
		cout << "Are you sure you'd like to restart?" << endl;
		char RestartAnswer = cin.get();
		cin.ignore(999, '\n');
		if (tolower(RestartAnswer) == 'y' or tolower(RestartAnswer) == 'r')
		{
			initializeStatus(rooms, currentRoom, inv, puz);    //  RESTART
		}
	}
	else if (word[0] == "save")
	{
		saveGame(Save, inv, currentRoom, rooms, puz);

	}

	else if (word[0] == "give" or word[0] == "feed" or word[0] == "unlock" or word[0] == "free" or word[0] == "use" or word[0] == "open"
		or word[0] == "offer" or word[0] == "sail" or word[0] == "leave" or word[0] == "use" or word[0] == "stab"
		and word[1] == "bananas" or word[1] == "banana" or word[1] == "gorilla" or word[1] == "treasure" or word[1] == "keys" or word[1] == "knife"
		or word[1] == "prisoner" or word[1] == "cell" or word[1] == "key" or word[1] == "keys" or word[1] == "treasure" or word[1] == "gold")
	{

	}

	else     // END OF ELSE IF STATEMENTS
	{
		cout << "Invalid command. Type 'commands' to see commands." << endl;
	}

	if (currentRoom == GCAVE)
	{
		puz.gorilla = true;
		puz.knife = true;
		puz.natives = true;
		puz.parrot = true;
		puz.prisoner = true;
	}

	//SHIPWHEEL/Gorrila puzzle
	if (currentRoom == SHIPWHEEL and !puz.gorilla)     // If gorilla puzzle has not been completed
	{
		if (word[0] == "give" or word[0] == "feed")
		{
			if (word[1] == "bananas" or word[1] == "banana" or word[1] == "gorilla")
			{
				if (inv.item.banana)
				{
					puz.gorilla = true;
					inv.item.banana = false;
					cout << "The gorilla is happy and satisfied. You may now approach the wheel" << endl;
					currentRoom = SHIPWHEEL;
				}
				else
				{
					cout << "You do not have bananas to offer" << endl;
				}
			}
			else if (word[1] == "treasure" or word[1] == "keys" or word[1] == "knife")
			{
				cout << "The gorilla throws it back at you" << endl;
			}
			else
			{
				cout << "Invalid command. Type 'help' to see commands." << endl;
			}
		}
		else
		{
			if (word[0] == "stab")
			{
				cout << "You attempt to stab the gorilla..." << endl;
				cout << "The gorilla ravages your body" << endl;
				cout << "You are dead" << endl;
				command = "quit";
			}
			else
			{
				cout << "There is a large gorilla by the ship's wheel. He is surrounded by banana peels." << endl;
				cout << "He looks dangerously hungry and you do not attempt to appraoch the wheel." << endl;
			}
		}
	}

	//GALLEY/Parrot puzzle
	if (currentRoom == GALLEY and !puz.parrot)   // If parrot puzzle not completed
	{
		cout << rooms[currentRoom].longd << endl << endl;
	}
	while (currentRoom == GALLEY and !puz.parrot)
	{
		cout << "The parrot does not let you leave" << endl;
		getline(cin, pcommand);
		i = 0;
		pcommand = pcommand + " ";
		while (pcommand != "")
		{
			blank = pcommand.find(' ');
			pword[i] = pcommand.substr(0, blank);
			pcommand = pcommand.erase(0, blank + 1);
			i++;
		}
		pcheck = pwordcheck(pword);
		if (not pcheck)
		{
			cout << endl;
			cout << "The parrot repeats you in a strange language" << endl;
			parrot(pword, i);
			cout << endl;
			cout << "There may be certain words that will set you free" << endl << endl;
		}
		else
		{
			puz.parrot = true;
			cout << "The parrot is happy and lets you leave!" << endl;
			cout << "It tells you a secret" << endl;
			cout << "'There is a secret compartment in the captain's quarters which contains the keys for the prisoner's cell'" << endl;
		}
	}

	//Brig/Prisoner puzzle
	if (currentRoom == BRIG and !puz.prisoner)  // If prisoner puzzle not completed
	{
		if (word[0] == "unlock" or word[0] == "free" or word[0] == "use" or word[0] == "open")
		{
			if (word[1] == "prisoner" or word[1] == "cell" or word[1] == "key" or word[1] == "keys")
			{
				if (inv.item.keys)
				{
					cout << "You free the prisoner! He is greatful and will now willingly become your servant" << endl;
					puz.prisoner = true;
				}
				else
				{
					cout << "You do not have keys to use" << endl;
				}
			}
			else
			{
				cout << "Try using keys" << endl;
			}
		}
		else
		{
			if (inv.item.keys)
			{
				cout << "You have keys you can use" << endl;
			}
			else
			{
				if (!inv.item.keys)
					cout << "You can't do that or you need to be more specific" << endl;
			}
		}
	}

	//Gangplank/Natives puzzle
	if (currentRoom == ISLAND and !puz.natives and rooms[ISLAND].returning and lastRoom == GANGPLANK)
	{
		cout << "The natives have blocked you and will not allow you to leave." << endl;
		cout << "They seem to be want a treasure chest from within the ship." << endl;
		currentRoom = GANGPLANK;
	}
	else
	{
		if (currentRoom == GANGPLANK and !puz.natives and rooms[GANGPLANK].returning)
		{
			if (word[0] == "give" or word[0] == "offer")
			{
				if (word[1] == "treasure" or word[1] == "gold")
				{
					if (inv.item.treasure)
					{
						cout << "The natives happily accept the treasure and allow you to roam their island" << endl;
						puz.natives = true;
						inv.item.treasure = false;
					}
					else
					{
						cout << "You do not have the treasure!" << endl;
					}
				}
				else
				{
					cout << "The natives do not accept your offering" << endl;
				}
			}
			else
				if (word[0] == "west" or word[0] == "w" or word[0] == "go"
					or word[0] == "look" or word[0] == "drop" or word[0] == "inventory" or word[0] == "help"
					or word[0] == "commands" or word[0] == "back")
				{

				}
				else
				{
					cout << "You can't do that, try again" << endl;
				}
		}
	}

	//ShipWheel/Win puzzle
	{
		if (currentRoom == SHIPWHEEL and puz.gorilla == true)
		{
			if (word[0] == "sail" or word[0] == "leave" or word[0] == "use")
			{
				if (puz.prisoner)
				{
					cout << "You sail away from the island and back to civilization!" << endl << endl;
					gameCheck = 1;
				}
				else
				{
					cout << "You may need another person to man the ship" << endl << endl;
				}
			}
		}
	}

	cout << endl;



	rooms[lastRoom].returning = true;
}



char EnumToChar(rooms RoomFind)   // Converts enumerated rooms back into strings for use in outputs
{
	switch (RoomFind)
	{

	case 0: return 'a';
	case 1: return 'b';
	case 2: return 'c';
	case 3: return 'd';
	case 4: return 'e';
	case 5: return 'f';
	case 6: return 'g';
	case 7: return 'h';
	case 8: return 'i';
	case 9:   return 'j';
	case 10: return 'k';
	case 11: return 'l';
	case 12: return 'm';
	}

}
