/* This is the main function that will use the numberguess object
The numberguess class is in separate files:
	numberguess.h - header file interface to the numberguess class
	numberguess.cpp - implementation of the numberguess member functions
*/

/*
STUDENT NAME: Kelvin Dhoman
Due Date: December 9, 2021
Course:  C0P3014
Assignment:  Program 12 Fall 2021
Professor: Sorgente
Description: number guessing game with a random number generator, class member functions, private and public member variables, and a player struct with a dynamic array
that keeps track of each player that has played the game and their score and if they won or lost.
*************************************************************/


#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator
#include "numberguess.h"

using namespace std;

//HERE IS THE main function
int main()
{
	//user input variable
	string yesOrNo = "y";
	//the game
	numberGuess activeGame;
	//keep track of the number of games
	int numGames = 0;
	//ask the user if they want to play
	cout << "Do you want to play the guessing game? (y(Y) or n(N)): ";
	cin >> yesOrNo;

	while (yesOrNo == "y" || yesOrNo == "Y")
	{
		//Increase the count of numGames for more players.
		numGames++;
		//playOneRound
		activeGame.PlayOneRound();
		//add one to the number of games
		activeGame.SetCount(numGames);//keep track of the number of games
		//play again?
		cout << endl << "Do you want to play the another round? (y(Y) or n(N)): ";
		cin >> yesOrNo; //Get users input to play another game.
	}

	//Print the leader board/games played
	activeGame.PrintGameResults();
	
	return 0;
}