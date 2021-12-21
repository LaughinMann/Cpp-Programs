/****PROGRAM 4 HEADER*******************************************************
STUDENT NAME: Kelvin Dhoman
Due Date: September 22, 2021
Course:  C0P3014
Assignment:  Program 4
Professor: Sorgente

Description:  A program that contains simple i/o in C++, control structures (if/ else if/ else), simple math in C++, data types string, double, and int,
formatting output in C++, functions, call by value and call by reference, a reiteration of the order calculator with utilization of data structures and file input and streaming.


*************************************************************/
#include <iostream> //standard library for i/o
#include <fstream>//you must include this library if you wish to do file i/o
#include <string> // always include this when you use the string class

using namespace std;

/*********************************************************
//Following is the declaration of a order record
**********************************************************/
struct orderRecord
{
	string cellNum;
	string itemNum;
	int quantity = 0;
	double price = 0.0;
	int locationID = 0;

	double taxRate = 0.0;
	double tax = 0.0;
	double netCost = 0.0;
	double totalCost = 0.0;
};

//Declaration/ Prototypes for your functions will go here
//BE SURE TO ADD COMMENTS TO THE FUNCTION PROTOTYPES AND THE FUNCTION DEFINITIONS
void DataFromFile(ifstream&, orderRecord&);
//Precondition: Connected to a file and must have a valid orderRecord.
//Postcondition: One line of data from the file at a time has been read into one orderRecord.
//Description: Reads the data from one orderRecord in the file.
void GetTaxRate(double&, int);
//Precondition: A current orderRecord must exist with locationID information.
//Postcondition: taxRate has been set for further order/pricing calculations.
//Description: Finds the tax rate based on the locationID.
void ProcessData(orderRecord&);
//Precondition: A valid current orderRecord has been read and inputted.
//Postcondition: The apporiate Tax Rate and calculations have been made based on orderRecord data.
//Description: Get the tax rate and make the appropriate calculations.
void PrintToScreen(const orderRecord&);
//Precondition: A valid orderRecord has been set and data has been apporiately inputted.
//Postcondition: The orderRecord(s) retrieved from a file have been outputted to the user.
//Description: Prints the results onto the screen.
void PrintCategoryHeaders();
//Precondition: The orderRecord loop must not have been called yet.
//Postcondition: The orderRecord data output to the user has been categorized correctly.
//Description: Simple function to print the category headers.

int main()
{
	//User's name variable
	string name;

	//Greet the user
	cout << "Enter your first name: ";
	cin >> name;
	cout << name << ", Let's get started processing the file data." << endl;

	//Declare the orderRecord
	orderRecord recordData;

	ifstream in;   //Declaring an input file stream.
	in.open("purchaseOrderData.txt"); //connect to the input file add the file name.

	//Print the column headings.
	if (in.fail())
	{
		cout << "Input file did not open correctly" << endl;
	}
	else
	{
		//Print categories text first.
		PrintCategoryHeaders();
		while (!in.eof()) //has not reached the end of the file.
		{
			//Retrieve data
			DataFromFile(in, recordData);
			//Process data
			ProcessData(recordData);
			//print to the screen
			PrintToScreen(recordData);
		}
	}

	//Close out of the file.
	in.close();
	//Say goodbye to the User
	cout << "\n" << name << ", have a nice day!";
	return 0;
}


//Function Implementations will go here

void DataFromFile(ifstream& in, orderRecord& currentRecord)
//Description:  Reads the data from one orderRecord in the file.
{
	//Read data for each each category from the records file.
	in >> currentRecord.cellNum;
	in >> currentRecord.itemNum;
	in >> currentRecord.quantity;
	in >> currentRecord.price;
	in >> currentRecord.locationID;
}

void GetTaxRate(double& taxRate, int locationID)
//Description:  Finds the tax rate based on the locationID.
{
	//use the location ID to set the tax rate
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
		cout << "\nZERO or A negative number for the location ID is not a valid entry. \n";
	}
}

void ProcessData(orderRecord& currentRecord)
//Description:  Get the tax rate and make the appropriate calculations.
{

	//Call the GetTaxRate function to get the tax rate 
	//based on the currentRecord.locationID
	GetTaxRate(currentRecord.taxRate, currentRecord.locationID);

	//If locationID is invalid set the price to 0 to cancel everything out
	if (currentRecord.locationID == 0)
		currentRecord.price = 0;
	
	//Do the calculations here for tax, net, and total
	//Math to calculate total tax and total cost of the items.
	currentRecord.tax = currentRecord.quantity * currentRecord.price * currentRecord.taxRate;
	currentRecord.netCost = currentRecord.quantity * currentRecord.price;
	currentRecord.totalCost = currentRecord.netCost + currentRecord.tax;

}

void PrintCategoryHeaders()
//Description: Simple function to print the category headers.
{
	// Headers for each of the order categories
	cout << "Phone Number" << "\t";
	cout << "Item Number" << "\t";
	cout << "Qty" << "\t";
	cout << "Price" << "\t";
	cout << "LocID" << "\t";
	cout << "Rate" << "\t";
	cout << "Tax" << "\t";
	cout << "Net" << "\t";
	cout << "Total" << "\n";
}

void PrintToScreen(const orderRecord& currentRecord)
//Description:  Prints the results onto the screen.
{
	//set the number of decimal places for doubles
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2); //use any number here for the number of decimal places

	// display the results here
	cout << currentRecord.cellNum << "\t";
	cout << currentRecord.itemNum << "\t";
	cout << currentRecord.quantity << "\t";
	cout << currentRecord.price << "\t";
	cout << currentRecord.locationID << "\t";

	cout.precision(4);//4 decimal places
	cout << currentRecord.taxRate << "\t";

	cout.precision(2);//back to 2 decimal places
	cout << currentRecord.tax << "\t";
	cout << currentRecord.netCost << "\t";
	cout << currentRecord.totalCost << "\n"; //Set new line for the next orderRecord
}