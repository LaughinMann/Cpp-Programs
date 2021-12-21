/****PROGRAM 3 HEADER*******************************************************
STUDENT NAME: Kelvin Dhoman
Due Date: September 15, 2021
Course:  C0P3014
Assignment:  Program 3
Professor: Sorgente

Description:  A program that contains simple i/o in C++, control structures (if/ else if/ else), simple math in C++, data types string, double, and int, 
formatting output in C++, functions, call by value and call by reference, a reiteration of the order calculator with utilization of data structures and file input and streaming.


*************************************************************/
#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class

using namespace std;

//ADD FUNCTION PROTOTYPES HERE
//BE SURE TO UPDATE the Comments Pre and Post Conditions, and Description

void GetOrder(string&, string&, int&, double&, int&);
//Precondition: All required variables (Phone #, Item #, Item Quanity, Item Price, and LocationID) must be declared before function is called.
//Postcondition: All the order data has been set to the apporiate variable based on the input from the User.
//Description:  Gets the order information by reference from the user.
void GetRate(double&, int);
//Precondition: Location ID must have been inputted and set from the GetOrder() function call.
//Postcondition: Tax Rate variable data has been set to a decimal format in order to calculate proper pricing.
//Description:  Sets the the tax rate by reference based on the value of the location ID.
void Calculate(int, double, double, double&, double&, double&);
//Precondition: All required variables must be declared or inputted from GetRate() function usage.
//Postcondition: The total, net and tax variables have been set.
//Description: Takes the quantity, price, and taxRate by copy and sets the tax, net, and total by reference.
void Display(string, string, int, double, int, double, double, double, double);
//Precondition: All required variables must be declared and/or inputted from GetOrder(), GetRate(), and Calculate() functions.
//Postcondition: All order and pricing information is displayed to user.
//Description: Pass all the information for each order by copy and display the results on the screen.

int main()
{

	string name; // First name of user we are interacting with.
	string phoneNumber; //Cell Phone number of user.
	string itemNumber; //Item number that was purchased from the user.
	string userInput; // Input of the user to repeat the loop or not for another calculation.

	int itemQuantity; //Quantity of items user has.
	double taxRate; //Tax rate based off of locationID.
	double tax; //The tax based off calculations.
	double net; //The net amount based off calculations.
	double total; //The total amount based off calulcations.
	double itemPrice; // The user's item price
	int locationID; // The user's location ID for Tax rate calculation.


	cout << "Enter your first name: ";
	cin >> name;

	//begin loop
	{
		//The code to get the user's input, perform the calculations, and print
		// the results to the screen should go here. 
		do
		{
			//Get Order information from user.
			GetOrder(phoneNumber, itemNumber, itemQuantity, itemPrice, locationID);
			//Calculate the tax rate based on their locationID.
			GetRate(taxRate, locationID);

			//Force item price to be 0 to cancel everything out if locationID is invalid.
			if (locationID <= 0)
				itemPrice = 0;

			//Calculate the tax amount, net cost, and total cost.
			Calculate(itemQuantity, itemPrice, taxRate, tax, net, total);
			//Display order information to user.
			Display(phoneNumber, itemNumber, itemQuantity, itemPrice, locationID, taxRate, tax, net, total);

			//Ask user if they want to repeat the loop to do another calculation or to say goodbye.
			cout << "\n" << name << ", Would you like to do another calculation (Y or N): \n";
			cin >> userInput;

			//Get User's input if they want to repeat the look for an order or not.
		} while (userInput == "y" || userInput == "Y");
	} //end loop
	
	//Say goodbye and exit program
	cout << "\n" << name << ", Have a nice day!";
	return  0;
}

//ADD FUNCTION DEFINITIONS HERE


//Description:  Gets the order information by reference from the user 
//**************************************************************************************
void GetOrder(string& cel, string& item, int& qty, double& price, int& loc)
{
	//ask and get the information from the user
	cout << "Enter the cell phone number: ";
	cin >> cel;

	//Get user's item number.
	cout << "Enter the item number? ";
	cin >> item;

	//Get the quanity of items the user has.
	cout << "Enter the quantity? ";
	cin >> qty;

	//Get the price of the item the user has.
	cout << "Enter the price? ";
	cin >> price;

	//Get the location ID from the user.
	cout << "Enter the location ID number? ";
	cin >> loc;
	cout << "\n"; //Spacer for calculation to make it look nicer.
}



//Description:  Sets the the tax rate by reference based on the value of the location ID.
//***************************************************************************************
void GetRate(double& taxRate, int locID)
{
	//If-else statment in order to find out correct tax rate by locationID.
	if (locID >= 1 && locID <= 15)
		taxRate = 0.0444;
	else if (locID >= 16 && locID <= 30)
		taxRate = 0.0525;
	else if (locID >= 31 && locID <= 45)
		taxRate = 0.0610;
	else if (locID > 45)
		taxRate = 0.9530;
	else if (locID <= 0) //If locationID is less than 0 which is invalid make tax 0 and item price 0 to cancel everything out.
	{
		taxRate = 0; //Set tax rate to 0 because of invalid locationID.
		cout << "ZERO or A negative number for the location ID is not a valid entry. \n";
	}
}



//Description: Takes the quantity, price, and taxRate by copy and sets the tax, net, and total by reference
//**********************************************************************************************************
void Calculate(int qty, double price, double taxRate, double& tax, double& net, double& total)
{
	//do the calculations here for tax, net, and total
	//Math to calculate total tax and total cost of the items.
	tax = qty * price * taxRate;
	net = qty * price;
	total = net + tax;
}


//Description: Pass all the information for each order by copy and display the results on the screen
//**************************************************************************************************************************************
void Display(string cel, string item, int qty, double price, int loc, double taxRate, double tax, double net, double total)
{
	//set the number of decimal places for doubles
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2); //use any number here for the number of decimal places

	//Printing all the information about user and their total price including tax information.
	cout << "Cell number: " << cel << "\n";
	cout << "Item number: " << item << "\n";
	cout << "Quantity: " << qty << "\n";
	cout << "Price: " << price << "\n";
	cout << "Tax Rate: " << (taxRate * 100) << "%" << "\n";
	cout << "Tax: $" << tax << "\n";
	cout << "Net cost: $" << net << "\n";
	cout << "Total cost: $" << total << "\n";
}