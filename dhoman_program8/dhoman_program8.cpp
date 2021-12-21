/****PROGRAM HEADER*******************************************************
STUDENT NAME: Kelvin Dhoman
Due Date: November 3, 2021
Course:  C0P3014
Assignment:  Program 8
Professor: Sorgente

Description: A simple hangman game that utilizes loops, classes, strings, file input streaming, and chars.

*************************************************************/

#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <fstream> //file input/ output
#include <cstdlib> //for exit()

using namespace std;

const int numGuesses = 6; //Six guesses (head, body, arm1, arm2, leg1, leg2

/*********************************************************
//Following is the declaration of a round of the hangman game
**********************************************************/
class hangmanGame
{
public:
	string solution; //Solution word
	string userGuess; //if the user guesses a correct letter they can guess the word
	char hintWord[20] = ""; //hint word made of *
	char lettersGuessed[20] = ""; //letters guessed so far (right or wrong)
	int letterCount = 0; //number of letters guessed so far (right or wrong)
	int incorrectCount = 0; //number of incorrect letters guessed so far
	char currentLetter = ' '; //current letter guess
	int wordLength = 0;//length of the solution word
	bool correctLetter = false; //flag to set if the letter is in the word
	bool win = false; //flag to set if all the user won that round
};

void HangmanRules(const string&);
//Description: Provides instructions to the user on how to play the game.

void SetUpOneRound(hangmanGame&, ifstream&);
//Precondition: A hangmanGame class variable must be declared and a input file variable must be initialized and file opened with data
//Postcondition: The member variables within the current active hangmanGame will be reset and a word will be loaded in as the solution
//Description: Get the word from the file and reset all member variables

void CreateHintWord(hangmanGame&);
//Precondition: A hangmanGame class variable must be declared and a solution must be set within it
//Postcondition: The hint word will be set within the hang man game's variable
//Description: Creates the array of * for the hint word for the game

void PlayHangman(const string&, hangmanGame&);
//Precondition: a string name variable must be declared and initialized, and a hangmanGame must be setup
//Postcondition: A round of hangman has been played and all variables have been updated for each round. 
//Description: Play one round of the hangman game

void GetLetterGuess(hangmanGame&);
//Precondition: A hangmanGame variable must be declared with a hintWord set up.
//Postcondition: Increments the amount of guesses done and what letters were guessed so far
//Description: Displays hint array and letters guessed asks and gets a current letter guess from 
//the user and adds it to the letters guessed array

bool InterpretLetterGuess(hangmanGame&);
//Precondition: A hangmanGame variable must be set along with a currentLetter, solution, and hintWord.
//Postcondition: Reveals the hint letter at the index of the word if the letters match. 
//Description: Check if the letter guessed is in the solution and if it is, replace all * with that 
//letter in the hintWord and return true, otherwise return false

void CorrectGuess(hangmanGame&, string name);
//Precondition: A hangmanGame variable must be declared, and a string inputted or string variable
//Postcondition: Sets win to within the hangmanGame variable to true if the guess was correct or prints out text.
//Description: Checks for the final correct letter and if it is not the final correct letter
//ask and get a word guess from the user if the user wants to guess the word 

bool GameOver(const hangmanGame&);
//Precondition: A hangmanGame variable must be declared
//Postcondition: Returns true or false depending of if the hint word or guess was correct
//Description: This function will return true if the hintWord matches the solution, you can use ==  
//or if the userGuess matches the solution, you can use ==.

void WonOrLostDisplay(const hangmanGame&, string name);
//Precondition: A hangmanGame must be declared and a user must have a name inputted or a string variable.
//Postcondition: Displays appropriate text if the player won or lost.
//Description: Lets the user know if they won or lost the round.

void DrawHangman(hangmanGame&);
//Precondition: A hangmanGame variable must be initialized and takes into account the incorrectCount.
//Postcondition: Outputs the hangman parts text and drawing based on the incorrectCount
//Description: Output the hangman parts text and drawing to the user

int main()
{
	//Declare variables
	hangmanGame activeGame; //Variable for the hangman game being played
	string userInput; //User input if they want to do another round
	string name; //User's name
	ifstream in; //Input file for the words

	//connect to the input file 
	in.open("inputWords.txt");

	//if file did not open correctly
	if (in.fail())
	{
		cout << "Input file did not open correctly" << endl;
		exit(1);
	}

	//ask and get the users name
	cout << "Enter your first name: ";
	cin >> name;

	//Show Hangman rules to player
	HangmanRules(name);

	cout << "Do you want to play the hangman game? (y or n): ";
	cin >> userInput;

	//loop to continue to play another round
	while (userInput != "n" && userInput != "N")
	{
		//set up the hangman round
		SetUpOneRound(activeGame, in);
		//play one round of hangman
		PlayHangman(name, activeGame);
		//again?
		cout << "\nDo you want to play another round? (y or n): ";
		cin >> userInput;
	}

	return  0;
}

//Function Implementations will go here
void HangmanRules(const string& name)
//Description:  provides instructions to the user on how to play the game
{
	cout << "\n\t" << name << ", WELCOME TO HANGMAN!\n\n";
	cout << "\n\tPlease read the following instructions before you play: \n\n";
	cout << "\t- You will be presented with a word to be guessed.\n";
	cout << "\t- Guess letters one at a time.\n";
	cout << "\t- You can have up to six incorrect letter guesses.\n";
	cout << "\t- You can only guess the word when you have made a correct letter guess.\n";
	cout << "\t- The game will be OVER when you have guessed the word correctly, \n\tor when you have guessed letters incorrectly SIX times.\n";
	cout << "\n\tHAVE FUN!\n\n";
}

void SetUpOneRound(hangmanGame& activeGame, ifstream& in)
//Description: Get the word from the file and reset all member variables
{
	// clear the solution word
	activeGame.solution = "";
	//clear userGuess string
	activeGame.hintWord[0] = '\0'; //clear the star array 
	//clear the lettersGuessed array
	activeGame.lettersGuessed[0] = '\0';
	//reset incorrect guesses
	activeGame.incorrectCount = 0;
	//letter count starts back at 0
	activeGame.letterCount = 0; 
	//reset the incorrectCount
	activeGame.correctLetter = false; //reset correctLetter to false
	//reset win to false
	activeGame.win = false;

	//get a word from the file
	in >> activeGame.solution;

	//create the hint word
	CreateHintWord(activeGame);
}

void CreateHintWord(hangmanGame& activeGame)
//Description: Creates the array of * for the hint word for the game
{
	//get the length of the word 
	activeGame.wordLength = (int)activeGame.solution.length(); //Casted to int to get rid of warning.
	//let the user know how many letters are in the word
	cout << "\nThe word has " << activeGame.wordLength << " letters\n\n";

	//use a loop to create the array of *
	for (int i = 0; i < activeGame.solution.length(); i++)
	{
		activeGame.hintWord[i] = '*';
	}
	//add the null ('\0') character 
	activeGame.hintWord[activeGame.wordLength] = '\0';
}

void PlayHangman(const string& name, hangmanGame& activeGame)
//Description:  Play one round of the hangman game
{
	//LOOP FOR THE ROUND OF THE GAME
	//the number of incorrect guesses is less than numGuesses
	//and win is false
	while (activeGame.incorrectCount < numGuesses && activeGame.win == false)
	{
		//GetLetterGuess
		GetLetterGuess(activeGame);
		//UpdateLetterArray - add the letter to the array of guessed letters
		
		if (InterpretLetterGuess(activeGame))
		{
			//the user guessed a correct letter
			cout << "\nThe letter was in the word!\n";
			//the user can now guess the word (if they want)
			CorrectGuess(activeGame, name);
		}
		else
		{
			//the user did not guess a correct letter
			cout << "\n" << name << ", your letter was not in the word!\nYou have added a body part!\n";
			activeGame.incorrectCount++;
		}
		//Draw(tell the user how many incorrect guesses so far)
		DrawHangman(activeGame);
	}

	//WonOrLostDisplay - lets the user know if they won or lost
	WonOrLostDisplay(activeGame, name);
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
}

void GetLetterGuess(hangmanGame& activeGame)
//Description:  Displays hint array and letters guessed asks and gets a current letter guess from 
//the user and adds it to the letters guessed array
{
	//display the hint array
	cout << "\n-----------------------------------------\n";
	cout << "\nHere is the word so far: \n\t";
	cout << activeGame.hintWord;
	cout << "\n-----------------------------------------\n";
	//display the letters that have been guessed so far
	cout << "Here are the letters guessed so far: \n\n";
	cout << activeGame.lettersGuessed;
	//ask and get a letter guess from the user
	cout << "\n\nEnter a letter: ";
	cin >> activeGame.currentLetter;
	cout << endl;
	//Add the letter guessed to the letters array
	activeGame.lettersGuessed[activeGame.letterCount] = activeGame.currentLetter;
	//update the letterCount
	activeGame.letterCount++;
	//add the '\0' character
	activeGame.lettersGuessed[activeGame.letterCount] = '\0';
}

bool InterpretLetterGuess(hangmanGame& activeGame)
//Description:  Check if the letter guessed is in the solution and if it is, replace all * with that 
//letter in the hintWord and return true, otherwise return false
{
	//Set rv to initially false.
	bool rv = false;

	//use a loop to search the solution word
	for (int i = 0; i < activeGame.wordLength; i++)
	{
		if (activeGame.currentLetter == activeGame.solution[i])
		{
			rv = true; //Letter was in solution
			activeGame.hintWord[i] = activeGame.currentLetter; //Replace letter in hint word with the correct letter
		}
	}

	return rv; //True if found a matching letter, false if no matching letter was found.
}

void CorrectGuess(hangmanGame& activeGame, string name)
//Description:  checks for the final correct letter and if it is not the final correct letter
//ask and get a word guess from the user if the user wants to guess the word 
{
	char guess;
	cout << "\n-----------------------------------------\n";
	//display the hint word
	cout << "Here is the word so far: " << activeGame.hintWord << endl;
	if (GameOver(activeGame)) //the correct letter completed the hint word	
	{
		activeGame.win = true;//they won the round by entering all the letters
	}
	else //the user entered a correct letter but it was not the final correct letter
	{
		//ask and get a response (y or n) if they want to guess the word
		cout << "\nIT WILL NOT COUNT AGAINST YOU IF YOU DO NOT GET THE CORRECT WORD!";
		cout << "\nWould you like to guess the FULL word (y or n)? ";
		cin >> guess;

		//If the player wants to guess the word
		if (guess == 'y' || guess == 'Y')
		{
			//prompt for the word 
			cout << "Enter your guess: ";
			//get the word from the user
			cin >> activeGame.userGuess;
			//see if the game is over 
			if (GameOver(activeGame)) //Check if word matches the solution
			{
				//Set the win condition to true.
				activeGame.win = true;
			}
			else
			{
				//Tell the user it wasn't the right word.
				cout << "\nTHAT WAS NOT THE CORRECT WORD!";
			}
		}
	}

}

bool GameOver(const hangmanGame& activeGame)
//Description:  This function will return true if the hintWord matches the solution, you can use ==  
//or if the userGuess matches the solution, you can use ==
{
	return activeGame.solution == activeGame.hintWord || activeGame.userGuess == activeGame.solution;
}

void WonOrLostDisplay(const hangmanGame& activeGame, string name)
//Description: Lets the user know if they won or lost the round
{
	cout << "\n-----------------------------------------";
	if (activeGame.win)
	{
		//tell the user they won that round
		cout << "\nYou won that round! Congratulations!\n";
	}
	else
	{
		//tell the user they did not win that round
		cout << "\nSorry " << name << ", you did not win that round!\n";
		//display the solution word
		cout << "\nThe word was " << activeGame.solution;
	}

}

void DrawHangman(hangmanGame& activeGame)
//Description: Output the hangman parts text and drawing to the user
{
	cout << "\n------------------------------------------------------";
	cout << "\nO-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<";
	cout << "\n------------------------------------------------------";
	
	//If the user has no incorrect guesses
	if (activeGame.incorrectCount == 0)
	{
		cout << "\nYou have no incorrect guesses yet! O-|--<";
	}
	//If user has 1 incorrect guess
	else if (activeGame.incorrectCount == 1)
	{
		cout << "\nHEAD\n - 1 of 6 incorrect guesses!";
	}
	//If user has 2 incorrect guesses
	else if (activeGame.incorrectCount == 2)
	{
		cout << "\nHEAD\nBODY\n - 2 of 6 incorrect guesses!";
	}
	//If user has 3 incorrect guesses
	else if (activeGame.incorrectCount == 3)
	{
		cout << "\nHEAD\nBODY\nARM 1\n - 3 of 6 incorrect guesses!";
	}
	//If user has 4 incorrect guesses
	else if (activeGame.incorrectCount == 4)
	{
		cout << "\nHEAD\nBODY\nARM 1\nARM 2\n - 4 of 6 incorrect guesses!";
	}
	//If user has 5 incorrect guesses
	else if (activeGame.incorrectCount == 5)
	{
		cout << "\nHEAD\nBODY\nARM 1\nARM 2\nLEG 1\n - 5 of 6 incorrect guesses!";
	}
	//If user has all 6 incorrect guesses
	else if (activeGame.incorrectCount == 6)
	{
		cout << "\nHEAD\nBODY\nARM 1\nARM 2\nLEG 1\nLEG 2\n - 6 of 6 incorrect guesses!";
	}
	//If the user somehow has higher than 6 or less than 0 guesses.
	else
	{
		cout << "You have an incorrect guess, I think";
	}

	//Design print out
	cout << "\n------------------------------------------------------";
	cout << "\nO-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<  O-|--<";
	cout << "\n------------------------------------------------------";
}