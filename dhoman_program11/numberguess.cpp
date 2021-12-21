//cpp file for the numberguess
#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator
#include "numberguess.h" //header file reference for numberguess
using namespace std;

//MEMBER FUNCTION DEFINTIONS GO HERE
//the default constructor is called when and object of numberGuess is declared
numberGuess::numberGuess()
{
	//cout << "The default constructor has been called\n";
	upperValue = 0; //15, 50, or 150
	numGuesses = 0; //4, 6, or 8
	currentGuess = 0; //current guess input by the user
	solution = 0; //pseudo random generated number
	above = false; //current guess above the solution
	below = false; //current guess below the solution
	small = 0; //lowest value for feedback
	large = 0; //highest value for feedback
}

void numberGuess::SetUpperRange(int upper)
//Mutator function
//Description: sets the upper value of the current round
{
	upperValue = upper;
}

int numberGuess::GetUpperRange() const
//Accessor function
//Description: returns the upper value(private member variable)
{
	return upperValue;
}

void numberGuess::SetNumGuesses(int num)
//Mutator function
//Description: Sets the number of guesses for the current round.
{
	//set number guesses.
	numGuesses = num;
}

//ADD THE REST OF THE MEMBER FUNCTIONS HERE
int numberGuess::GetNumGuesses() const
//Accessor function
//Description: return the current number guesses (private member variable)
{
	return numGuesses;
}

int numberGuess::GetSolution() const {
	//Accessor function
	//Description: Return solution to player as an int.
	return solution;
}

void numberGuess::GuessInput()
//Description: Displays the range, prompts, and gets the next guess from the user.
{
	//Set the small and large variables (small is done for you)
	if (below)
	{
		//If the small hint is lower than the current guess change the small hint to a higher small.
		if (small < currentGuess)
		{
			small = currentGuess;
		}
	}

	if (above)
	{
		//If the large hint is higher than the current guess change the large hint to a lower high.
		if (large > currentGuess)
		{
			large = currentGuess;
		}
	}

	//Hint update according to the new limits
	cout << "Enter a guess between " << small << " and " << large << " : ";
	//Get the guess
	cin >> currentGuess;
}

bool numberGuess::ProcessGuess()
//Description: Returns true if the guess matches the solution else returns false.
{
	//If guess is too high let the user know.
	if (currentGuess > solution)
	{
		cout << "\nYour guess was too high.";
		cout << "\n-----------------------";
		above = true;
		return false;
	}
	//If guess is too low let the user know.
	else if (currentGuess < solution)
	{
		cout << "\nYour guess was too low.";
		cout << "\n-----------------------";
		below = true;
		return false;
	}
	//If guess is right let the bool return true and end game.
	else if (currentGuess = solution)
	{
		return true;
	}

	//Return all paths return just in-case
	return false;
}

void numberGuess::GenerateSolution()
//Description: Generates a game solution
{
	srand((unsigned)time(0));
	solution = 1 + rand() % upperValue;
}

void numberGuess::PlayOneRound(const string& name, numberGuess& currentGame)
//Description:  Play one round of the number guess game
{
	//Variable for i which is the current guess
	int i = 0;
	//initialize bool values (public member variables)
	currentGame.above = 0;
	currentGame.below = 0;

	//set the upper range based on the level (LevelRange function)
	//SetUpLevel(currentGame);
	cout << "\nYou will have " << currentGame.GetNumGuesses() << " guess, Good Luck!" << endl;

	//initialize high and low values
	currentGame.small = 1;
	currentGame.large = currentGame.GetUpperRange(); //accessor function
	//generate the random number
	currentGame.GenerateSolution();

	//loop(number of guesses)
	do
	{
		cout << "\nThis is guess number (" << i + 1 << " of " << currentGame.GetNumGuesses() << ")" << endl;
		//get next guess public member function
		currentGame.GuessInput();
		//reset above and below bool values to false
		currentGame.below = 0;
		currentGame.above = 0;

		//Increment guess remaining counter that counts towards the max guesses
		i++;

		if (currentGame.ProcessGuess())
		{
			cout << "\nYou won that round, " << name << "!\n";
			i = currentGame.GetNumGuesses(); //(accessor function)
		}

	} while (i < currentGame.GetNumGuesses());

	//print the solution if the guesses is greater than the guesses left
	if (i >= currentGame.GetNumGuesses())
	{
		//Display the solution when they win or lose
		cout << endl << "\nTHE SOLUTION WAS " << currentGame.GetSolution() << endl;
		cout << endl << "--------------------------------------------------" << endl;
	}
}