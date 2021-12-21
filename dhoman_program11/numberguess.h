//header file for numberguess
#ifndef NUMBERGUESS_H
#define NUMBERGUESS_H

#include<iostream>
using namespace std;

class numberGuess
{
public:
	//default constructor
	numberGuess();

	//These functions are public and can be accessed anywhere.
	void SetUpperRange(int); //Sets the upper range for the round (mutator)
	void SetNumGuesses(int);  //Sets the number of guesses for the round (mutator)
	int GetUpperRange() const; //Returns the value of the private member variable (accessor)
	int GetNumGuesses() const; // Returns the value of the private member variable (accessor)
	int GetSolution() const; //Returns the value of the private member variable (accessor)

	void PlayOneRound(const string& name, numberGuess& currentGame); //Play a round of the game.
	void GenerateSolution(); //Generates the solution number.
	bool ProcessGuess(); //Determines if the guess is right or wrong.
	void GuessInput(); //Gets the next guess input from the user.

	bool above;	//current guess above the solution
	bool below;	//current guess below the solution
	int small;	//lowest value for feedback
	int large;	//highest value for feedback
private:
	int upperValue;	//15, 50, or 150
	int numGuesses;	//4, 6, or 8
	int currentGuess; //current guess input by the user
	int solution; //pseudo random generated number
};

#endif NUMBERGUESS_H