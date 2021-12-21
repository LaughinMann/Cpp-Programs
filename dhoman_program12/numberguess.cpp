//cpp file for the numberguess

#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator
#include "numberguess.h"

using namespace std;

//member function definitions will go here
//default constructor
numberGuess::numberGuess()
{
	cout << "------------------------------------------------\n";
	cout << "The default constructor has been called\n";
	count = 0;
	size = 1;
	playerList = new Player[size];
	playerList[0].upperValue = 0;//15, 50, or 150
	//set all variables for the first player to 0
	small = 0;
	large = 0;
	above = false;
	below = false;
}

//copy constructor
numberGuess::numberGuess(const numberGuess& gameObject)
{
	cout << "------------------------------------------------\n";
	cout << "The copy constructor has been called\n";
	count = gameObject.count;
	size = gameObject.size;
	playerList = new Player[size];
	for (int i = 0; i < count; i++)
	{
		playerList[i] = gameObject.playerList[i];
	}
	small = 0;
	large = 0;
	above = false;
	below = false;
}

//destructor
numberGuess::~numberGuess()
{
	delete[] playerList;
}

//left_side = right_side
//overload assignment operator uses *this pointer
numberGuess& numberGuess::operator = (const numberGuess& right_side)
{
	//if the same object occurs on both sides of the assignment
	//example game1 = game1;
	if (this == &right_side)
	{
		return *this;
	}
	else
	{
		//delete the playList of the guessGame on the left side of the =
		//assignment operator
		delete[] playerList; //remove the playList of the existing object
		cout << "------------------------------------------------\n";
		cout << "The overload assignment operator has been called\n";
		count = right_side.count;//set the count
		size = right_side.size;	//set the capacity
		playerList = new Player[size];	//new play list

		//copy all the players
		for (int i = 0; i < count; i++)
		{
			playerList[i] = right_side.playerList[i];
		}
		
		small = 0;
		large = 0;
		above = false;
		below = false;
		return *this;
	}
}

void numberGuess::SetUpLevel()
//sets up a round of the game
{
	do {
		cout << "************************************************\n";
		cout << "What level (Enter 1, 2, or 3) do you want to play? \n(1) Level 1 - 4 guesses, numbers 1 through 15 \n" 
			 << "(2) Level 2 - 6 guesses, numbers 1 through 50\n" 
			 << "(3) Level 3 - 8 guesses, numbers 1 through 150\n";
		cin >> playerList[count].level;
	} while (playerList[count].level > 3 || playerList[count].level < 1);

	//levels
	if (playerList[count].level == 1)
	{
		playerList[count].numGuesses = 4;
		playerList[count].upperValue = 15;
	}
	else if (playerList[count].level == 2)
	{
		playerList[count].numGuesses = 6;
		playerList[count].upperValue = 50;
	}
	else if (playerList[count].level == 3)
	{
		playerList[count].numGuesses = 8;
		playerList[count].upperValue = 150;
	}
	else //Invalid choice statement
	{
		cout << "\nThat is not a valid level";
	}
}
void numberGuess::PlayOneRound()
//Description:  Play one round of the number guess game
{
	//Variable for i which is the current guess
	int i = 0;
	
	//test and double
	TestAndDouble();
	//get the players name
	cout << "Enter your first name: ";
	cin >> playerList[count].name;
	//set up level
	SetUpLevel();

	//initialize variables above and below 
	above = 0;
	below = 0;

	//initialize high and low values
	small = 1;
	large = playerList[count].upperValue;

	//Guesses total sentence print out
	cout << "\nYou will have " << playerList[count].numGuesses << " guesses, Good Luck!" << endl;

	//generate the random number
	GenerateSolution();

	//loop(number of guesses)
	do
	{
		cout << "\n-----------------------";
		cout << "\nThis is guess number (" << i + 1 << " of " << playerList[count].numGuesses << ")";
		//get the next guess
		GuessInput();
		//reset above and below bool values to false
		below = 0;
		above = 0;

		//Increment Guess Counter
		i++;

		if (ProcessGuess())
		{
			//tell the user they won
			cout << "\nYou won that round, " << playerList->name << "!\n";
			//Set guesses
			i = playerList[count].numGuesses;
			//stop the loop without a break statement
			playerList[count].wonOrLost = 1;
		}
	} while (i < playerList[count].numGuesses);
	
	//Print solution
	cout << endl << "\nTHE SOLUTION WAS " << playerList[count].solution << endl;
	cout << endl << "--------------------------------------------------" << endl;
}


void numberGuess::GuessInput()
//Description:  Displays the range, prompts, and gets the next guess from the user
{
	//member variables for if the guess is below or above the solution
	if (below)
	{
		if (small < playerList[count].currentGuess)
		{
			small = playerList[count].currentGuess;
		}
	}
	if (above)
	{
		if (large > playerList[count].currentGuess)
		{
			large = playerList[count].currentGuess;
		}
	}

	//Enter a guess
	cout << "\nEnter a guess between " << small << " and " << large << " : ";
	cin >> playerList[count].currentGuess;
}

bool numberGuess::ProcessGuess()
//Description:  Describe what the function does.
{
	if (playerList[count].currentGuess > playerList[count].solution)
	{
		cout << "\nYour guess was too high.";
		cout << "\n-----------------------";
		above = true;
		return false;
	}
	//If guess is too low let the user know.
	else if (playerList[count].currentGuess < playerList[count].solution)
	{
		cout << "\nYour guess was too low.";
		cout << "\n-----------------------";
		below = true;
		return false;
	}
	//If guess is right let the bool return true and end game.
	else if (playerList[count].currentGuess = playerList[count].solution)
	{
		return true;
	}

	//Return all paths return just in-case
	return false;
}
void numberGuess::GenerateSolution()
{

	srand((unsigned)time(0));
	playerList[count].solution = 1 + rand() % playerList[count].upperValue;
	//cout << "\nSolution is " << solution << endl;

}

void numberGuess::TestAndDouble()
//dynamically double the size of the player list
{
	//Double the size
	if (count == size)
	{
		size *= 2;
	}

	//Declare a temp pointer and use new to allocate an array with “size” elements for the player size array 
	Player* temp = new Player[size];

	//Use a loop to copy all the players in the gameList over to temp (one by one) NOTE: there are only “count” number of elements in the gameList   
	for (int i = 0; i < count; i++)
	{
		temp[i] = playerList[i];
	}

	//after copying one by one from the original player list to temp delete the old player list   
	delete[] playerList;
	//assign temp to player list, player list will now have a player list that is double the size
	playerList = temp;

	//Print out count and size
	cout << "\ncount is " << count;
	cout << "\nsize is " << size << endl;
}

void numberGuess::PrintGameResults()
//prints the player, level, wonOrLost on the screen
{
	cout << "\n***********************************\n";
	cout << "Name\t" << "Level\t" << "won or lost\n";
	//use a loop to print the name, level, wonOrlost onto
	for (int i = 0; i < count; i++)
	{
		cout << playerList[i].name << "\t" << playerList[i].level << "\t" << playerList[i].wonOrLost << endl;
	}
}

//sets the number of players
void numberGuess::SetCount(int numPlayers)
{
	count = numPlayers;
}