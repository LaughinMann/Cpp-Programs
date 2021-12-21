/*
STUDENT NAME: Kelvin Dhoman
Due Date: November 10, 2021
Course:  C0P3014
Assignment:  Program 9 PART A Dynamic Array
Professor: Sorgente

Description: Number guessing game with a random number generator dynamic array to store game results.

*************************************************************/
#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator
#include <fstream> //output file
using namespace std;

/*********************************************************
//Following is the declaration of a round of numberGuess
**********************************************************/
class numberGuess
{
public:
	int level = 0;//game level 1,2, or 3
	int upperValue = 0;//15, 50, or 150
	int numGuesses = 0;//4, 6, or 8
	int currentGuess = 0; //current guess input by the user
	int solution = 0; //pseudo random generated number
	int small = 0;//lowest value for feedback
	int large = 0;//highest value for feedback
	bool above = false;//current guess above the solution
	bool below = false;//current guess below the solution
	string name; //name of current player
	bool wonOrLost = 0; //true or false for the current round of the game
};

void SetUpperRange(numberGuess& currentGame);
//Precondition: A numberGuess class variable must be initialized and a level from 1-3 must have been set in the class reference for the game.
//Postcondition: The upperValue of the numberGuess class variable has been set based on selected level.
//Description: Sets the upper value of the current game based on the level.

void SetNumGuesses(numberGuess&);
//Precondition: A numberGuess class variable must be initialized and a level from 1-3 must be set in the class referenced variable for the game.
//Postcondition: The max number of guesses of the numberGuess class reference variable has been set based on selected level.
//Description: Sets the maximum number of guesses for the current round based on the level.

void PlayOneRound(numberGuess&);
//Precondition: A numberGuess class variable must be used.
//Postcondition: A match of the number guessing game has been started and played.
//Description: Play one round of the number guessing game.

void GuessInput(numberGuess&);
//Precondition: A numberGuess game must have been initialized.
//Postcondition: A guess has been received from the user and the new upper or lower hint has been set and a remaining guess has been decremented.
//Description: Displays the range, prompts, and gets the next guess from the user.

bool ProcessGuess(numberGuess& currentGame);
//Precondition: A currentGuess class reference variable and has been initialized, and a solution was generated or set in the class reference to compare with currentGuess.
//Postcondition: Returns true or false if right or wrong, if wrong let player know and if guess was too high or low.
//Description: Returns true if the guess matches the solution returns false if they do not match lets the user know if the guess was too high or too low.

void GenerateSolution(numberGuess&);
//Precondition: A numberGuess class reference variable must have been initialized and a upperValue must have been set.
//Postcondition: A solution has been generated based on the current level and its upperLevel value.
//Description: Generates the solution number in the correct range.

void PrintGameResults(numberGuess numGameList[], int gameCount);
//Precondition: An array of numberGuess games must be declared and initialized, and a int for the games played must be set. 
//Postcondition: Will print out the game stats of each game played to the console and to a file named "numberGuessResults.txt".
//Description: Connects to an output file
//Prints the array results onto the screen and into the output file

void TestAndDouble(numberGuess*& numGameList, int count, int& size);
//Precondition: A numberGuess game array must be initialized and declared, a count variable and a size variable must be declared and initialized to compare to in order to double.
//Postcondition: Will double the size of the number game list array size to allow for more games.
//Description: Tests and doubles the size capacity of numGameList when count is the same as the size

int main()
{
	string userInput; //Player inputted choice variable
	numberGuess* gamesArray; //Games Array for the players
	int gameArraySizeCounter = 0; //Counter for the game area to increase
	int gamesArraySize = 1; // Game Array initial size to be doubled
	int currentGameCount = 0; //Current game counter

	//Set initial player/rounds limit
	gamesArray = new numberGuess[gamesArraySize];

	//Ask the user to play
	cout << "Do you want to play the guessing game? (y(Y) or n(N)): ";
	cin >> userInput;

	//Print out the size and count
	cout << endl << "count is: " << gameArraySizeCounter << endl;
	cout << "size is: " << gamesArraySize << endl;

	//while begin loop
	while (userInput != "n" && userInput != "N")
	{
		//Increment round count and test it to see if need to double the size array
		gameArraySizeCounter++;
		TestAndDouble(gamesArray, gameArraySizeCounter, gamesArraySize);
		//ask for the name here, it may be a different player
		cout << "Enter your first name: ";
		//into the member variable name
		cin >> gamesArray[currentGameCount].name;
		//Play one round of the game
		PlayOneRound(gamesArray[currentGameCount]);
		//add one to the game count.
		currentGameCount++;
		//Play again?
		cout << "Do you want to play the another round? (y(Y) or n(N)): ";
		cin >> userInput; //Get users input to play another game.

		//Print out the size and count
		cout << endl << "count is: " << gameArraySizeCounter << endl;
		cout << "size is: " << gamesArraySize << endl;
	}
	//Print the game results
	PrintGameResults(gamesArray, currentGameCount);
	return  0;
}

void PrintGameResults(numberGuess numGameList[], int gameCount)
{
	//Output stream
	ofstream out;
	//Filename variable
	string filename;
	//Ask user for input file
	cout << "Enter the output file (incl. extension): ";
	cin >> filename;
	//Open the output file
	out.open(filename, ios::app);
	cout << "\n***********************************\n";
	cout << "Name\t" << "Level\t" << "won or lost\n";
	//Use a loop to print the array (name, level, WonOrLost) onto the screen
	for (int i = 0; i < gameCount; i++)
	{
		cout << numGameList[i].name << "\t" << numGameList[i].level << "\t" << numGameList[i].wonOrLost << endl;
	}

	out << "\n***********************************\n";
	out << "Name\t" << "Level\t" << "won or lost\n";
	//Use a loop to print the array (name, level, WonOrLost) into the file
	for (int i = 0; i < gameCount; i++)
	{
		out << numGameList[i].name << "\t" << numGameList[i].level << "\t" << numGameList[i].wonOrLost << endl;
	}

	//Close the file
	out.close();
}

//Function Implementations will go here
void SetUpperRange(numberGuess& currentGame)
//Description: Sets the upper value of the current game based on the level
{
	if (currentGame.level == 1) //If level requested is 1 then the upper level hint is 15.
		currentGame.upperValue = 15;
	else if (currentGame.level == 2) //If level requested is 2 then the upper level hint is 50.
		currentGame.upperValue = 50;
	else if (currentGame.level == 3) //If level requested is 3 then the upper level hint is 150.
		currentGame.upperValue = 150;
}

void SetNumGuesses(numberGuess& currentGame)
//Description: Sets the maximum number of guesses for the current round based on the level
{
	if (currentGame.level == 1) //If level requested is 1 then the max guesses is 4.
		currentGame.numGuesses = 4;
	else if (currentGame.level == 2) //If level requested is 2 then the max guesses is 6.
		currentGame.numGuesses = 6;
	else if (currentGame.level == 3) //If level requested is 3 then the max guesses is 8.
		currentGame.numGuesses = 8;
}

void PlayOneRound(numberGuess& currentGame)
//Description:  Play one round of the number guess game
{
	//Ask what level the user wants to play and the game information
	do {
		cout << "************************************************" << endl;
		cout << "What level (Enter 1, 2, or 3)?" << endl;
		cout << "(1) Level 1 - 4 guesses, numbers 1 through 15." << endl;
		cout << "(2) Level 2 - 6 guesses, numbers 1 through 50." << endl;
		cout << "(3) Level 3 - 8 guesses, numbers 1 through 150." << endl;
		cin >> currentGame.level; //Set the current game's level class reference variable value to 1, 2, or 3.
	} while (currentGame.level > 3 || currentGame.level < 1); //Force user to pick a valid game number between 1-3.

	//Set the upper range based on the level
	SetUpperRange(currentGame);
	//Set the max guesses based on the level
	SetNumGuesses(currentGame);
	//Generate the random number solution
	GenerateSolution(currentGame);

	//initialize bool and high/low values
	currentGame.above = 0;
	currentGame.below = 0;
	currentGame.small = 1;
	currentGame.large = currentGame.upperValue;
	currentGame.wonOrLost = 0;

	//cout << "PLAY small: " << currentGame.small << endl;
	//cout << "PLAY large: " << currentGame.large << endl;

	//Variables for guess counter information
	int currentOutOfGuess = 1; //Used for the counter to decided the out of guesses.
	int maxNumberOfGuesses = currentGame.numGuesses; //Set the max guesses again for the counter.

	//Loop header, counting loop for the number of guesses
	do
	{
		//Counter that starts at 1 and goes to the max number of allowed guesses.
		if (currentGame.numGuesses < maxNumberOfGuesses)
			currentOutOfGuess++;

		cout << "\n-----------------------";
		//Tell the user what guess number they are on
		cout << "\nThis is guess number " << "(" << currentOutOfGuess << " of " << maxNumberOfGuesses << ")" << endl;
		//Get the next guess
		GuessInput(currentGame);
		//Reset above and below bool values to false
		currentGame.below = 0;
		currentGame.above = 0;

		//If the bool returns true and is the right answer tell them they won and end the loop.
		if (ProcessGuess(currentGame))
		{
			cout << "\nYou won that round, " << currentGame.name << "!";
			currentGame.numGuesses = 0; //Breaks the loop by just setting the guess numbers remaining to 0.
		}
	} while (currentGame.numGuesses > 0);
	//Tell the user the solution after the round of the game is done
	if (currentGame.numGuesses <= 0)
	{
		//Display the solution when they win or lose
		cout << endl << "\nTHE SOLUTION WAS " << currentGame.solution << endl;
		cout << endl << "--------------------------------------------------" << endl;
	}
}


void GuessInput(numberGuess& currentGame)
//Description: Displays the range, prompts, and gets the next guess from the user.
{
	//Set the small and large variables (small is done for you)
	if (currentGame.below)
	{
		//If the small hint is lower than the current guess change the small hint to a higher small.
		if (currentGame.small < currentGame.currentGuess)
		{
			currentGame.small = currentGame.currentGuess;
		}
	}

	if (currentGame.above)
	{
		//If the large hint is higher than the current guess change the large hint to a lower high.
		if (currentGame.large > currentGame.currentGuess)
		{
			currentGame.large = currentGame.currentGuess;
		}
	}

	//Hint print out that's update
	cout << "Enter a guess between " << currentGame.small << " and " << currentGame.large << " : ";
	//Get the guess
	cin >> currentGame.currentGuess;
	//Decrement the number of guesses.
	currentGame.numGuesses--;
}

bool ProcessGuess(numberGuess& currentGame)
//Description: Returns true if the guess matches the solution
//returns false if they do not match
//lets the user know if the guess was too high or too low
{
	//If guess is too high let the user know.
	if (currentGame.currentGuess > currentGame.solution)
	{
		cout << "\nYour guess was too high.";
		cout << "\n-----------------------";
		currentGame.above = true;
		return false;
	}
	//If guess is too low let the user know.
	else if (currentGame.currentGuess < currentGame.solution)
	{
		cout << "\nYour guess was too low.";
		cout << "\n-----------------------";
		currentGame.below = true;
		return false;
	}
	//If guess is right let the bool return true and end game.
	else if (currentGame.currentGuess = currentGame.solution)
	{
		currentGame.wonOrLost = true;
		return true;
	}

	return false;
}

//Description: Tests and doubles the size capacity of numGameList when count is the same as the size
void TestAndDouble(numberGuess*& numGameList, int count, int& size)
{
	//Multiply by 2
	if (count == size) //Double size once the round count is the max to prevent crashing.
		size *= 2;
	//Declare a numberGame pointer and use new to allocate an array with “size” elements 
	numberGuess* temp = new numberGuess[size];
	//Use a loop to copy all the numberGames in the gameList over to temp (one by one) NOTE: there are only “count” number of elements in the gameList   

	for (int i = 0; i < count; i++)
	{
		temp[i] = numGameList[i];
	}
	//after copying one by one from gameList to temp delete gameList   
	delete [] numGameList;
	//assign temp to gameList – // you will now have a gameList that is double the size
	numGameList = temp;
}

void GenerateSolution(numberGuess& currentGame)
//Description:  Generates the solution number in the correct range
{
	srand((unsigned)time(0));
	currentGame.solution = 1 + rand() % currentGame.upperValue;
	//cout << "\nSolution is " << currentGame.solution << endl;
}