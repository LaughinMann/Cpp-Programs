/****PROGRAM 2 HEADER*******************************************************
Kelvin Dhoman
Due Date: September 08, 2021
Course:  C0P3014
Assignment:  Program 2
Professor: Sorgente

Description: Simple i/o program that is written in C++ that incoporates loops in order to calculate the tax, net cost and total cost of an online order.


*************************************************************/

#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
using namespace std;

int main()
{
	string name; // First name of user we are interacting with.
	string phoneNumber; //Cell Phone number of user.
	string itemNumber; //Item number that was purchased from the user.
	string userInput; // Input of the user to repeat the loop or not for another calculation.

	int itemQuantity; //Quantity of items user has.
	double itemPrice; // The user's item price
	int locationID; // The user's location ID for Tax rate calculation.

	//Get user's first name.
	cout << "Enter your first name: ";
	cin >> name;

	//begin loop
	{
		do {
			//Get user's cell phone number.
			cout << "Enter the cell phone number: ";
			cin >> phoneNumber;

			//Get user's item number.
			cout << "Enter the item number? ";
			cin >> itemNumber;

			//Get the quanity of items the user has.
			cout << "Enter the quantity? ";
			cin >> itemQuantity;

			//Get the price of the item the user has.
			cout << "Enter the price? ";
			cin >> itemPrice;

			//Get the location ID from the user.
			cout << "Enter the location ID number? ";
			cin >> locationID;
			cout << "\n"; //Spacer for calculation to make it look nicer.

			double taxRate; //Tax rate depending on locationID.

			//If-else statment in order to find out correct tax rate by locationID.
			if (locationID >= 1 && locationID <= 15)
				taxRate = 0.0444;
			else if (locationID >= 16 && locationID <= 30)
				taxRate = 0.0525;
			else if (locationID >= 31 && locationID <= 45)
				taxRate = 0.0610;
			else if (locationID > 45)
				taxRate = 0.9530;
			else if (locationID <= 0) //If locationID is less than 0 which is invalid make tax 0 and item price 0 to cancel everything out.
			{
				taxRate = 0; //Set tax rate to 0 because of invalid locationID.
				itemPrice = 0; //Set to 0 so the rest of the math cancels everything out.
				cout << "ZERO or A negative number for the location ID is not a valid entry. \n";
			}

			double tax; //Tax rate depending on locationID.
			double netCost; // The net cost of all the items.
			double totalCost; // Total cost of all the items with tax included.

			//Math to calculate total tax and total cost of the items.
			tax = itemQuantity * itemPrice * taxRate;
			netCost = itemQuantity * itemPrice;
			totalCost = netCost + tax;

			//Magic formula to output all cout's to 2 decimal places below this segment of code.
			cout.setf(ios::fixed);
			cout.setf(ios::showpoint);
			cout.precision(2);

			//Printing all the information about user and their total price including tax information.
			cout << "Cell number: " << phoneNumber << "\n";
			cout << "Item number: " << itemNumber << "\n";
			cout << "Quantity: " << itemQuantity << "\n";
			cout << "Price: " << itemPrice << "\n";
			cout << "Tax Rate: " << (taxRate * 100) << "%" << "\n";
			cout << "Tax: $" << tax << "\n";
			cout << "Net cost: $" << netCost << "\n";
			cout << "Total cost: $" << totalCost << "\n";

			//Ask user if they want to repeat the loop to do another calculation or to say goodbye.
			cout << "\n" << name << ", Would you like to do another calculation (Y or N): \n";
			cin >> userInput;

		} while (userInput == "y" || userInput == "Y");
	}//end loop
	cout << "\n" << name << ", Have a nice day!";
	return  0;
}