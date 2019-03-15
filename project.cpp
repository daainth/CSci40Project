#include <iostream>
#include <fstream>
#include <iso646.h>
#include <string>
using namespace std;

enum rooms{TREE,ISLAND/*OCEAN*/,UPPERDECK,SHIPWHEEL,BOTTOMDECK,GALLEY,BRIG,CAPTAINQUARTERS,CARGOHOLD};

void PigLatin();
void instruct();
void gorilla();
void banana();
void natives();
void prisoner();


int main()
{
	int x;
	string command;
	cout << "You have just awakened on a strange island with a terrible headache." << endl;
	cout << "You can't remember anything about yourself or where you are." << endl;
	cout << "Type 'help' to view instructions" << endl;
	cin >> command;
	/*while (gameisnotOver)
	{
		execute command;
		read nextcommand;
	}*/


	return 0;
}

/*A function which converts commands into pig latin and exits once 
"hello", "polly", or "cracker"is input. Once input, it tells the player
about a secret compartment in the captain's quarters containing the keys
to the prisoner cell*/
void PigLatin()
{

}

//Tells the user the instructions to the game
void instruct()
{

}

/*A function that deals with interaction with the gorilla.
It will not leave unless given a banana*/
void gorilla()
{

}

/*A function that deals with the natives. 
They will not leave unless given treasure found in the trunk
of the cargo hold. */
void natives()
{

}

/* A function that deals with the the prisoner.
The player needs the prisoner's help to man the ship and leave*/
void prisoner()
{

}

/*A function that deals with the banana tree.
A knife is needed to cut the banana*/
void banana()
{

}