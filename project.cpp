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
bool gameOver=false;

enum rooms { TREE, ISLAND/*OCEAN*/, UPPERDECK, SHIPWHEEL, BOTTOMDECK, GALLEY, BRIG, CAPTAINQUARTERS, CARGOHOLD, NOROOM };

void execute(string);


int main()
{
	int x;
	string command;
	cout << "You have just awakened on a strange island with a terrible headache." << endl;
	cout << "You can't remember anything about yourself or where you are." << endl;
	cout << "Type 'help' to view instructions" << endl;
	getline(cin, command);
	while (command not gameOver)
	{
		execute(command);
		getline(cin, command);
	}


	return 0;
}

void execute(string command)
{

}
