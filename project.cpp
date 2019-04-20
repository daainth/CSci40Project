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
string Vend = "yay";
string Cend = "ay";

//Eventually possibly include "Ocean" to rooms
enum rooms { TREE, ISLAND, GANGPLANK, UPPERDECK, SHIPWHEEL, BOTTOMDECK, GALLEY, BRIG, CAPTAINQUARTERS, CARGOHOLD, NOROOM };

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


void initialize(roomType[NOROOM]);    // Has to be roomtype[NOROOM] for some reason

void execute(string, rooms&, rooms, roomType[NOROOM], inventory&, puzzle&, int&); // roomType has an & next to it because we need the function to return the current room

void parrot(string[],int);//PigLatin
int check(string);//PigLatin
string piglatin(string);//PigLatin
int VowelFind(string);//PigLatin
bool pwordcheck(string[]);

void invent(inventory);

int main()
{
	inventory inv;
	puzzle puz;
	int gameCheck;
	gameCheck = 0;
	inv.item.knife = false;
	inv.item.banana = false;
	inv.item.treasure = false;
	inv.item.keys = false;
	puz.knife = false;
	puz.gorilla = false;
	puz.natives = false;
	puz.parrot = false;
	puz.prisoner = false;
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
			cout << room[currentRoom].shortd << endl << endl;
		}
		else
		{
			cout << room[currentRoom].longd << endl << endl;
		}


		getline(cin, command);
		execute(command, currentRoom, lastRoom, room, inv, puz, gameCheck);

		if (currentRoom == NOROOM)    // NOROOM is used when you cannot go into an area
		{
			cout << "You can't go that way" << endl;
			currentRoom = lastRoom;  //Sets current room to whatever room you were in before
		}
		if (gameCheck == 1)
		{
			command = "quit";
		}
		lastRoom = currentRoom;
		gameOver = command == "quit";

	}
	cout << "You won! Congratulations" << endl;
	return 0;
}


void execute(string command, rooms& currentRoom, rooms lastRoom, roomType rooms[NOROOM], inventory& inv, puzzle& puz, int& gameCheck)
{
	string word[2], pword[15];
	int blank, i;
	string pcommand;
	bool pcheck;
	command = command + " ";
	i = 0;
	while (command != "" and i<=1)
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
		currentRoom = rooms[currentRoom].direction.south;
	}
	if (word[0] == "east" or word[0] == "e" or word[1] == "east" or word[1] == "e")
	{
		currentRoom = rooms[currentRoom].direction.east;
	}
	if (word[0] == "west" or word[0] == "w" or word[1] == "west" or word[1] == "w")
	{
		currentRoom = rooms[currentRoom].direction.west;
	}
	if (word[0] == "north" or word[0] == "n" or word[1] == "north" or word[1] == "n")
	{
		currentRoom = rooms[currentRoom].direction.north;
	}
	if (word[0] == "up" or word[0] == "u" or word[1] == "up" or word[1] == "u")
	{
		currentRoom = rooms[currentRoom].direction.up;
	}
	if (word[0] == "down" or word[0] == "d" or word[1] == "down" or word[1] == "d")
	{
		currentRoom = rooms[currentRoom].direction.down;
	}

	//SHIPWHEEL/Gorrila puzzle
	if (currentRoom == SHIPWHEEL and !puz.gorilla)
	{
		if (word[0] == "give" or word[0] == "feed")
		{
			if (word[1] == "bananas" or word[1] == "banana" or word[1] == "gorilla")
			{
				if (inv.item.banana)
				{
					puz.gorilla = true;
					inv.item.banana = false;
					cout << "The gorilla is happy and satisfied. You may now approach the wheel" << endl << endl;
					currentRoom = SHIPWHEEL;
				}
				else
				{
					cout << "You do not have bananas to offer" << endl << endl;
				}
			}
			else
			{
				cout << "The gorilla throws it back at you" << endl << endl;
			}
		}
		else
		{
			cout << "There is a large gorilla by the ship's wheel. This gorilla is hostile. You can't approach the wheel." << endl << endl;
		}
	}

	//GALLEY/Parrot puzzle
	if (currentRoom == GALLEY and !puz.parrot)
	{
		cout << rooms[currentRoom].longd << endl << endl;
	}
	while (currentRoom == GALLEY and !puz.parrot)
	{
		cout << "The parrot does not let you leave" << endl << endl;
		
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
			parrot(pword,i);
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
	if (currentRoom == BRIG and !puz.prisoner)
	{
		if (word[0] == "unlock" or word[0] == "free" or word[0] == "use")
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
					cout << "You do not have keys to use" << endl << endl;
				}
			}
			else
			{
				if (word[1] == "")
				{
					if (inv.item.keys)
					{
						cout << "Try using the keys" << endl;
					}
				}
				else
				cout << "The cell remains locked" << endl << endl;
			}
		}
	}

	//Gangplank/Natives puzzle
	if (currentRoom == ISLAND and !puz.natives and rooms[ISLAND].returning and lastRoom==GANGPLANK)
	{
		cout << "The natives have blocked you and will not allow you to leave," << endl;
		cout << "maybe giving them something from the ship will make them leave." << endl;
		currentRoom = GANGPLANK;
	}
	else
	{
		if (currentRoom == GANGPLANK and !puz.natives and rooms[GANGPLANK].returning)
		{
			if (word[0] == "give" or word[0] == "offer")
			{
				if (word[1] == "treasure")
				{
					if (inv.item.treasure)
					{
						cout << "The natives happily accept the treasure and allow you to roam their island" << endl << endl;
						puz.natives = true;
					}
					else
					{
						cout << "The natives do not accept your offering" << endl << endl;
					}
				}
			}
			else
			{
				if (word[0] == "give" or word[0] == "offer")//Can make this specific to the item offered***
				cout << "The natives do not accept your offering" << endl << endl;
			}
		}
	}

	//ShipWheel/Win puzzle
	{
		if (currentRoom == SHIPWHEEL and puz.gorilla==true)
		{
			if (word[0] == "sail" or word[0] == "leave")
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

	if (currentRoom == NOROOM)    // NOROOM is used when you cannot go into an area
	{
		cout << "You can't go that way" << endl << endl;
		currentRoom = lastRoom;  //Sets current room to whatever room you were in before
	}



	if (word[0] == "take" or word[0] == "grab" or word[0] == "pickup" or word[0]=="get")    // PICK UP STUFF
	{
		if (word[1] == "keys")
		{
			if (rooms[currentRoom].item.keys)
			{
				if (puz.parrot)
				{
					if (rooms[currentRoom].item.keys)
					{
						rooms[currentRoom].item.keys = false;
						inv.item.keys = true;
						cout << "You got the keys!" << endl;
					}
					else
						cout << "No keys here bucko" << endl;
				}
				else
				{
					cout << "No keys here bucko" << endl;
				}
			}
			else
			{
				cout << "No keys here bucko" << endl;
			}
		}


		if (word[1] == "banana")
		{
			if (rooms[currentRoom].item.banana)
			{
				if (inv.item.knife)
				{
					if (rooms[currentRoom].item.banana)
					{
						//rooms[currentRoom].item.banana = false;
						inv.item.banana = true;
						cout << endl;
						cout << "You cut down a banana!" << endl;;
					}
					/*&else
						cout << "No bananas here" << endl;*/
				}
				else
					cout << "You'll need a knife to cut these down." << endl;
			}
			else
				cout << "There are no bananas here buddy" << endl;
		}

		if (word[1] == "knife" or word[1] == "blade")
		{
			if (rooms[currentRoom].item.knife)
			{
				rooms[currentRoom].item.knife = false;
				inv.item.knife = true;
				cout << "You found a knife!" << endl;

			}
			else
				cout << "There is no knife here!" << endl;
		}
		if (word[1] == "treasure")
		{
			if (rooms[currentRoom].item.treasure)
			{
				rooms[currentRoom].item.treasure = false;
				inv.item.treasure = true;
				cout << "You take the treasure!" << endl;
			}
		}
	}

	if (word[0] == "eat")
	{
		if (word[1] == "banana")
		{
			if (inv.item.banana)
			{
				cout << "chomp chomp chomp" << endl;
				cout << "..." << endl;
				cout << "You ate the banana!" << endl;
				inv.item.banana = false;
			}
		}
	}


	if (word[0] == "drop" or word[0] == "place")    // DROP STUFF
	{
		if (inv.item.keys)
		{
			if (word[1] == "keys")
			{
				inv.item.keys = false;
				rooms[currentRoom].item.keys = true;
				cout << "You dropped the keys" << endl;
			}
		}
		else
			cout << "You dont have the keys" << endl;

	}
	cout << endl;

	if (word[0] == "help")
	{
		cout << "You can input up to two words to use as actions" << endl;
		cout << "'go west' or just 'west'- will take you west or 'pickup keys' will pickup the keys" << endl;
		cout << "You may also type 'look' to recieve a longer description of where you are at" << endl;
		cout << "Inputting 'inventory' will show you your current items" << endl;
		cout << endl << endl;
	}

	if (word[0] == "look")
	{
		cout << rooms[currentRoom].longd << endl << endl;
	}

	if (word[0] == "inventory")
	{
		cout << "You have :" << endl;
		invent(inv);
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
	rooms[TREE].item.knife = false;
	rooms[TREE].item.banana = true;
	rooms[TREE].item.treasure = false;
	rooms[TREE].item.keys = false;



	rooms[ISLAND].longd = "The island is forested with banana trees. Most of the bananas are green, but one tree to your west might have ripe bananas. There are ominous drums in the background. There is a ship to your east with a gangplank to the shore";
	rooms[ISLAND].shortd = "You are at the island";
	rooms[ISLAND].direction.north = NOROOM;
	rooms[ISLAND].direction.south = NOROOM;
	rooms[ISLAND].direction.west = TREE;
	rooms[ISLAND].direction.east = GANGPLANK;
	rooms[ISLAND].direction.up = NOROOM;
	rooms[ISLAND].direction.down = NOROOM;
	rooms[ISLAND].returning = false;
	rooms[ISLAND].item.knife = false;
	rooms[ISLAND].item.banana = false;
	rooms[ISLAND].item.treasure = false;
	rooms[ISLAND].item.keys = false;


	rooms[GANGPLANK].longd = "You are aboard the Gangplank. The ocean surrounds you. To your east is the entrance to the ship's upperdeck.";
	rooms[GANGPLANK].shortd = "You are on the GangPlank.";
	rooms[GANGPLANK].direction.north = NOROOM;
	rooms[GANGPLANK].direction.south = NOROOM;
	rooms[GANGPLANK].direction.west = ISLAND;
	rooms[GANGPLANK].direction.east = UPPERDECK;
	rooms[GANGPLANK].direction.up = NOROOM;
	rooms[GANGPLANK].direction.down = NOROOM;
	rooms[GANGPLANK].returning = false;
	rooms[GANGPLANK].item.knife = false;
	rooms[GANGPLANK].item.banana = false;
	rooms[GANGPLANK].item.treasure = false;
	rooms[GANGPLANK].item.keys = false;


	rooms[SHIPWHEEL].longd = "You are at the wheel.";
	rooms[SHIPWHEEL].shortd = "You are at the wheel.";
	rooms[SHIPWHEEL].direction.north = NOROOM;
	rooms[SHIPWHEEL].direction.south = UPPERDECK;
	rooms[SHIPWHEEL].direction.west = NOROOM;
	rooms[SHIPWHEEL].direction.east = NOROOM;
	rooms[SHIPWHEEL].direction.up = NOROOM;
	rooms[SHIPWHEEL].direction.down = NOROOM;
	rooms[SHIPWHEEL].returning = false;
	rooms[SHIPWHEEL].item.knife = false;
	rooms[SHIPWHEEL].item.banana = false;
	rooms[SHIPWHEEL].item.treasure = false;
	rooms[SHIPWHEEL].item.keys = false;


	rooms[UPPERDECK].longd = "The top deck has a wheel at the north end of the ship, and the south end of the ship has a ladder down to the lower deck. ";
	rooms[UPPERDECK].shortd = "You are at the upperdeck";
	rooms[UPPERDECK].direction.north = SHIPWHEEL;
	rooms[UPPERDECK].direction.south = CAPTAINQUARTERS;
	rooms[UPPERDECK].direction.west = GANGPLANK;
	rooms[UPPERDECK].direction.east = NOROOM;
	rooms[UPPERDECK].direction.up = NOROOM;
	rooms[UPPERDECK].direction.down = BOTTOMDECK;
	rooms[UPPERDECK].returning = false;
	rooms[UPPERDECK].item.knife = false;
	rooms[UPPERDECK].item.banana = false;
	rooms[UPPERDECK].item.treasure = false;
	rooms[UPPERDECK].item.keys = false;


	rooms[BOTTOMDECK].longd = "The deck below is dimly lit, and smells musty. You can make out three doors. One is to the east, one is to the west, and one is a trapdoor below you.";
	rooms[BOTTOMDECK].shortd = "You are at the bottomdeck";
	rooms[BOTTOMDECK].direction.north = NOROOM;
	rooms[BOTTOMDECK].direction.south = NOROOM;
	rooms[BOTTOMDECK].direction.west = CARGOHOLD;
	rooms[BOTTOMDECK].direction.east = GALLEY;
	rooms[BOTTOMDECK].direction.up = UPPERDECK;
	rooms[BOTTOMDECK].direction.down = BRIG;
	rooms[BOTTOMDECK].returning = false;
	rooms[BOTTOMDECK].item.knife = false;
	rooms[BOTTOMDECK].item.banana = false;
	rooms[BOTTOMDECK].item.treasure = false;
	rooms[BOTTOMDECK].item.keys = false;

	rooms[GALLEY].longd = "This is the galley. It is mostly empty, but in a shadowy corner you see a parrot sitting on a perch.";
	rooms[GALLEY].shortd = "You are at the galley";
	rooms[GALLEY].direction.north = NOROOM;
	rooms[GALLEY].direction.south = NOROOM;
	rooms[GALLEY].direction.west = BOTTOMDECK;
	rooms[GALLEY].direction.east = NOROOM;
	rooms[GALLEY].direction.up = NOROOM;
	rooms[GALLEY].direction.down = NOROOM;
	rooms[GALLEY].returning = false;
	rooms[GALLEY].item.knife = false;
	rooms[GALLEY].item.banana = false;
	rooms[GALLEY].item.treasure = false;
	rooms[GALLEY].item.keys = false;

	rooms[BRIG].longd = "In this room there is a prisoner in a locked cell. He says,'Jack, I'm so glad you're alive. The captain locked me up for cheating at cards, which is the only reason the islanders didn't capture me. They killed everyone else. Now I guess we're the only two left, which makes you captain since you were first mate. Go find the keys to unlock this door, and we can sail out of here.'";
	rooms[BRIG].shortd = "You are at the brig";
	rooms[BRIG].direction.north = NOROOM;
	rooms[BRIG].direction.south = NOROOM;
	rooms[BRIG].direction.west = NOROOM;
	rooms[BRIG].direction.east = NOROOM;
	rooms[BRIG].direction.up = BOTTOMDECK;
	rooms[BRIG].direction.down = NOROOM;
	rooms[BRIG].returning = false;
	rooms[BRIG].item.knife = false;
	rooms[BRIG].item.banana = false;
	rooms[BRIG].item.treasure = false;
	rooms[BRIG].item.keys = false;

	rooms[CAPTAINQUARTERS].longd = "You are now at the captain's quarters and there is a bed and a table in this room.(There is a knife on the table.)";
	rooms[CAPTAINQUARTERS].shortd = "You are at the captain's quarters";
	rooms[CAPTAINQUARTERS].direction.north = UPPERDECK;
	rooms[CAPTAINQUARTERS].direction.south = NOROOM;
	rooms[CAPTAINQUARTERS].direction.west = NOROOM;
	rooms[CAPTAINQUARTERS].direction.east = NOROOM;
	rooms[CAPTAINQUARTERS].direction.up = NOROOM;
	rooms[CAPTAINQUARTERS].direction.down = NOROOM;
	rooms[CAPTAINQUARTERS].returning = false;
	rooms[CAPTAINQUARTERS].item.knife = true;
	rooms[CAPTAINQUARTERS].item.banana = false;
	rooms[CAPTAINQUARTERS].item.treasure = false;
	rooms[CAPTAINQUARTERS].item.keys = true;

	rooms[CARGOHOLD].longd = "You've entered the cargo hold. There are barrels, a pile of tools, and a trunk. (Treasure is in the trunk.)";
	rooms[CARGOHOLD].shortd = "You are at the cargohold";
	rooms[CARGOHOLD].direction.north = NOROOM;
	rooms[CARGOHOLD].direction.south = NOROOM;
	rooms[CARGOHOLD].direction.east = BOTTOMDECK;
	rooms[CARGOHOLD].direction.west = NOROOM;
	rooms[CARGOHOLD].direction.up = NOROOM;
	rooms[CARGOHOLD].direction.down = NOROOM;
	rooms[CARGOHOLD].returning = false;
	rooms[CARGOHOLD].item.knife = false;
	rooms[CARGOHOLD].item.banana = false;
	rooms[CARGOHOLD].item.treasure = true;
	rooms[CARGOHOLD].item.keys = false;

}

void parrot(string word[],int count)//Remove check
{
	int i;
	i = 0;
	while (i<=count-1)
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
