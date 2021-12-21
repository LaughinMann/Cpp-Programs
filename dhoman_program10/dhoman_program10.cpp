/*
STUDENT NAME: Kelvin Dhoman
Due Date: November 17, 2021
Course:  C0P3014
Assignment:  Program 10 Fall 2021
Professor: Sorgente
Description: number guessing game with a random number generator
introduction to class member functions, private and public member
variables mutator and accessor functions.
*************************************************************/

#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator

using namespace std;
/*********************************************************
//Following is the declaration  numberGame
**********************************************************/
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

//FUNCTION PROTOTYPES
void PlayOneRound(const string&, numberGuess&);
//Precondition: A string variable for the user's name must be set and a numberGuess class variable must be used.
//Postcondition: A match of the number guessing game has been started and played.
//Description: Play one round of the number guessing game.

//function prototype for SetUpLevel NOT a member function
void SetUpLevel(numberGuess&);
//Precondition: A numberGuess variable must be declared.
//Postcondition: The level is set according to the player's input and the variables are set for the guesses, and the max upper limit.
//Description: Asks and gets the level and sets up one round of the game

//HERE IS THE main function
int main()
{
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
		//play a round
		PlayOneRound(name, numberGame);
		//another round?
		cout << endl << "Do you want to play the another round? (y(Y) or n(N)): ";
		cin >> yesOrNo; //Get users input to play another game.
	}

	return  0;
}

//HERE IS THE PlayOneRound function
//The following 2 functions are not member functions
//to help understand private member variables
//Use accessor and mutator functions
void PlayOneRound(const string& name, numberGuess& currentGame)
//Description:  Play one round of the number guess game
{
	//Variable for i which is the current guess
	int i = 0;
	//initialize bool values (public member variables)
	currentGame.above = 0;
	currentGame.below = 0;
	
	//set the upper range based on the level (LevelRange function)
	SetUpLevel(currentGame);
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
	}
}