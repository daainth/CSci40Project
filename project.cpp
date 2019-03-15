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
