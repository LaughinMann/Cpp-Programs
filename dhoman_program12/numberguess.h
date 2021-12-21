//header file for numberguess
#ifndef NUMBERGUESS_H
#define NUMBERGUESS_H

#include<iostream>
using namespace std;

struct Player {
	string name;
	int level = 0;//1,2, or 3
	bool wonOrLost = 0;
	int upperValue = 0;//15, 50, or 150
	int numGuesses = 0;//4, 6, or 8
	int currentGuess = 0;//current guess input by the user
	int solution = 0;//pseudo random generated number
};

class numberGuess
{
public:
	//constructor
	numberGuess();

	//copy constructor
	numberGuess(const numberGuess& gameObject);

	//destructor
	~numberGuess();

	//overload assignment operator
	numberGuess& operator =(const numberGuess& right_side);
	void SetUpLevel();//sets up a round of the game
	void PlayOneRound();//plays one round of the game
	void GuessInput(); //gets the next guess from the user
	bool ProcessGuess(); //determines if the guess is right or wrong
	void GenerateSolution(); //generates the solution
	void TestAndDouble();//dynamically double the size of the player list
	void PrintGameResults();
	void setInput(int output);

	//prints the player, level, wonOrLost on the screen
	void SetCount(int count);//mutator function 
	
	//sets the count of the number of players
	int small;//lowest value for feedback
	int large;//highest value for feedback
	bool above;//current guess above the solution
	bool below;//current guess below the solution
private:
	Player* playerList;//dynamic array of players
	int count;//number of players
	int size;//capacity of player list
};

#endif NUMBERGUESS_H