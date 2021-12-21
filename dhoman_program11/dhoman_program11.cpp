/* This is the main function that will use the numberguess object
The numberguess class is in separate files:
	numberguess.h - header file interface to the numberguess class
	numberguess.cpp - implementation of the numberguess member functions
*/

/*
STUDENT NAME: Kelvin Dhoman
Due Date: December 3, 2021
Course:  C0P3014
Assignment:  Program 11 Fall 2021
Professor: Sorgente
Description: number guessing game with a random number generator
introduction to class member functions, private and public member
variables mutator and accessor functions along with seperate compilation with header files and a cpp file.
*************************************************************/


#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator
#include "numberguess.h"

using namespace std;

//function prototype for SetUpLevel NOT a member function
void SetUpLevel(numberGuess&);
//Precondition: A numberGuess variable must be declared.
//Postcondition: The level is set according to the player's input and the variables are set for the guesses, and the max upper limit.
//Description: Asks and gets the level and sets up one round of the game

//HERE IS THE main function
int main()
{
	int point{};

	do
	{
		cout << "Enter sin point: ";
		cin >> point;
		cout << endl << getSin(point) << endl;
	} while (point < 1000);

	//Name and user input variables
	string name;
	string yesOrNo = "y";
	//declare an object variable of type numberGuess
	numberGuess numberGame;
	//get the user's name
	cout << "Enter your first name: ";
	cin >> name;
	//want to play?
	cout << "Do you want to play the guessing game? (y(Y) or n(N)): ";
	cin >> yesOrNo;

	while (yesOrNo != "n" && yesOrNo != "N")
	{
		//Set up levels
		SetUpLevel(numberGame);
		//play a round
		numberGame.PlayOneRound(name, numberGame);
		//another round?
		cout << endl << "Do you want to play the another round? (y(Y) or n(N)): ";
		cin >> yesOrNo; //Get users input to play another game.
	}

	return  0;
}

void SetUpLevel(numberGuess& currentGame)
//Asks and gets the level and sets up one round of the game
{
	//Level variable
	int level;
	do {
		//Ask and get the level
		cout << "************************************************" << endl;
		cout << "What level (Enter 1, 2, or 3)?" << endl;
		cout << "(1) Level 1 - 4 guesses, numbers 1 through 15." << endl;
		cout << "(2) Level 2 - 6 guesses, numbers 1 through 50." << endl;
		cout << "(3) Level 3 - 8 guesses, numbers 1 through 150." << endl;
		cin >> level;
	} while (level > 3 || level < 1);

	//Level if-else statements
	if (level == 1) //Level 1
	{
		//mutator functions
		currentGame.SetNumGuesses(4);
		currentGame.SetUpperRange(15);
	}
	else if (level == 2) // Level 2
	{
		//mutator functions
		currentGame.SetNumGuesses(6);
		currentGame.SetUpperRange(50);
	}
	else if (level == 3) //Level 3
	{
		//mutator functions
		currentGame.SetNumGuesses(8);
		currentGame.SetUpperRange(150);
	}
	else //Invalid choice statement
	{
		cout << "\nThat is not a valid level";

		string name = "Kelvin";

		if (name == "K" || name[0] == 'k')

	}
}