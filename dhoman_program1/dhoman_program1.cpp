/****PROGRAM 1 HEADER****************************************
Kelvin Dhoman
Due Date: September 1, 2021
Course: COP3014
Assignment: Program 1
Professor: Sorgente

Description: Simple i/o C++ program that asks for the user's name and allows user to enter their number of quarters, dimes, and nickels and then outputs
the total monetary value of the coins in cents.

*************************************************************/

#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
using namespace std;

int main()
{
    //First name of the user inputting their coins.
    string name;
    //Declare variables for their quarters, dimes, and nickels the user has and the total in cents as ints.
    int number_of_quarters, number_of_dimes, number_of_nickels, total_in_cents;
 
    //Ask user for their first name.
    cout << "Enter your first name: ";
    cin >> name;
    //Ask for how many quarters user has and store it in number_of_quarters.
    cout << "Hello " << name << ", how many quarters do you have? \n";
    cin >> number_of_quarters;
    //Ask for how many dimes does the user have and store it in number_of_dimes.
    cout << "How many dimes do you have? \n";
    cin >> number_of_dimes;
    //Ask for how many nickels does the user have and store it in number_of_nickels.
    cout << "Finally, how many nickels do you have? \n";
    cin >> number_of_nickels;

    //Multiply everything to cent values.
    total_in_cents = (number_of_quarters * 25) + (number_of_dimes * 10) + (number_of_nickels * 5);

    //Output the total in cents to user.
    cout << "In total, your coins are worth " << total_in_cents << " cents.";
    return 0;
}