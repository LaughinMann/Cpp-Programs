#include "Header.h"
#include <string>

using namespace std;

// write your solution here
void ContestResult::setWinner(string in)
{
	winner = in;
}

void ContestResult::setSecondPlace(string in)
{
	winner = in;
}

void ContestResult::setThirdPlace(string in)
{
	winner = in;
}

string ContestResult::getWinner()
{
	return winner;
}

string ContestResult::getSecondPlace()
{
	return secondPlace;
}

string ContestResult::getThirdPlace()
{
	return thirdPlace;
}
