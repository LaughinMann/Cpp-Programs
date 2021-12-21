/****PROGRAM 5 HEADER*******************************************************
STUDENT NAME: Kelvin Dhoman
Due Date: September 29, 2021
Course:  C0P3014
Assignment:  Program 5
Professor: Sorgente

Description: Area and Perimeter Calculator using predefined functions, programmer defined functions, call by reference, call by value, and structs.

*************************************************************/
#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <cmath> //for sqrt

using namespace std;

/*********************************************************
//Following is the declaration of the Shape data
**********************************************************/
struct shape
{
	double area = 0.0;
	double perimeter = 0.0;
	double side1 = 0.0;
	double side2 = 0.0;
	double side3 = 0.0;
};

void MenuChoices(string& choice);
//Precondition: A choice string variable must be declare before being called. 
//Postcondition: Registers the user's choice to either be invalid, a triangle, a rectangle or to quit.
//Description: Shows to user a menu of possible choices and takes an input for their choice of shape or to quit the program.
void ProcessChoice(string& choice, shape&);
//Precondition: Must have a valid choice input parameter and a declared shape variable from the shape struct.
//Postcondition: Processes the validity of the chosen shape and presents appropriate data used to calculate area and perimeter.
//Description: Gets the inputted choice and processes the desired shape to see if it's valid or not to further make calculations.
void TriangleCalculator(shape&);
//Precondition: Shape struct variable data must have been inputted such as side1, side2, and side3 and must be a valid real triangle.
//Postcondition: The triangle's area and perimeter has been calculated based on inputted sides struct data.
//Description: Gets all valid triangle data and calculates the Area and Perimeter using Heron's Formula.
void RectangleCalculator(shape&);
//Precondition: Shape struct variable data must have been inputted with only side1 and side2 having data inputted, side 3 is ignored.
//Postcondition: The rectangles's area and perimeter has been calculated based on inputted sides struct data.
//Description: Gets all valid rectangle data and calculates the Area and Perimeter.

//HERE IS THE main function, the driver to test your functions
int main()
{
	//declare variables
	shape shapeData; // Struct shape variable for Triangle or Rectangle data
	string choice; // Variable to get the selected choice being a T/t or R/r from the user

	//Magic formula for decimal print outs
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(3); //display the area to 3 decimal places

	//One-time Greeting to user
	cout << "Welcome to the area and perimeter calculator!";

	do //begin loop
	{
		//Menu - Display choices and instructions
		MenuChoices(choice);
		//Process selection - Process the user's choice and data
		ProcessChoice(choice, shapeData);

		//If choice isn't to QUIT then show the shape calculations
		if ((choice != "Q") && (choice != "q"))
		{
			cout.precision(3); //display the area and perimeter to 3 decimal places
			cout << "\n\nThe area is: " << shapeData.area; //Shape area print out
			cout << "\n\nThe perimeter is: " << shapeData.perimeter << "\n"; //Shape perimeter print out
		}
	} while ((choice != "Q") && (choice != "q")); //end loop

	//Close out of program if they want to quit.
	cout << "\nGoodbye, Have a great day!";
	return 0;
}


//Description: Shows to user a menu of possible choices and takes an input for their choice of shape or to quit program. 
void MenuChoices(string& choice) {
	//Print out block for instructions
	cout << "\n----------------------------------------------";
	cout << "\n\nPlease enter a T, R, or Q.";
	cout << "\n\nTo calculate: ";
	cout << "\nThe area and perimeter of a triangle, enter T.";
	cout << "\nThe area and perimeter of a rectangle, enter R.";
	cout << "\n----------------------------------------------";
	cout << "\nEnter Q to quit: ";
	//User input becomes the choice variable
	cin >> choice;
}

//Description: Gets the inputted choice and processes the desired shape to see if it's valid or not to make calculations.
void ProcessChoice(string& choice, shape& shape)
{
	//If inputted choice is not any of the valid choices (Upper and Lowercase) then output it's an invalid choice and restart.
	if ((choice != "t") && (choice != "T") && (choice != "r") && (choice != "R") && (choice != "Q") && (choice != "q"))
	{
		cout << "\nThat input is not recognized!"; //If invalid shape tell user and zero out area and perimeter.
		shape.area = 0;
		shape.perimeter = 0;
	}

	//If requested shape is a Triangle.
	else if (choice == "T" || choice == "t")
	{
		//Get input of the triangle sides data.
		cout << "\n*********************************************";
		cout << "\nEnter the length of side one: ";
		cin >> shape.side1;
		cout << "Enter the length of side two: ";
		cin >> shape.side2;
		cout << "Enter the length of side three: ";
		cin >> shape.side3;

		//Condition-checking for if it's a valid triangle.
		if ((shape.side1 + shape.side2 < shape.side3) || (shape.side1 + shape.side3 < shape.side2) || (shape.side2 + shape.side3 < shape.side1))
		{
			//Invalid triangle, ZERO everything out and restart calculator.
			cout << "\nNot a valid triangle!";
			shape.area = 0;
			shape.perimeter = 0;
		}
		else
		{
			//If everything is OK process the correct data in the calculator.
			cout << "------------------------------------\n";
			cout << "Side A\t Side B\t Side C\n";
			cout.precision(1); //display JUST the side data to 1 decimal place based on program 5 sample output instructions.
			cout << shape.side1 << "\t " << shape.side2 << "\t " << shape.side3;
			//Do calculations based on inputted side data.
			TriangleCalculator(shape);
		}
	}
	//If requested shape is a Rectangle.
	else if (choice == "R" || choice == "r")
	{
		//Get input of the rectangle sides data.
		cout << "\n*********************************************";
		cout << "\nEnter the length of side one: ";
		cin >> shape.side1;
		cout << "Enter the length of side two: ";
		cin >> shape.side2;
		cout << "------------------------------------\n";
		cout << "Side X\t Side Y\t\n";
		cout.precision(1); //display JUST the side data to 1 decimal place based on program 5 sample output instructions.
		cout << shape.side1 << "\t " << shape.side2 << "\t ";
		//Do calculations based on inputted side data.
		RectangleCalculator(shape);
	}
}

//Description: Gets all valid triangle data and calculates the Area and Perimeter using Heron's Formula.
void TriangleCalculator(shape& shape)
{
	//Area Calculation using Heron's Formula
	//Semi-Perimeter Calculation
	double s = ((shape.side1 + shape.side2 + shape.side3) / 2);
	//Triangle Area Final Calculation
	shape.area = sqrt(s * ((s - shape.side1) * (s - shape.side2) * (s - shape.side3)));
	//Perimeter Final Calculation
	shape.perimeter = shape.side1 + shape.side2 + shape.side3;
}

//Description: Gets all valid rectangle data and calculates the Area and Perimeter.
void RectangleCalculator(shape& shape)
{
	//Rectangle basic Area formula using it's base * width.
	shape.area = shape.side1 * shape.side2;
	//Rectangle basic Perimeter formula adding up the 4 sides through multiplication.
	shape.perimeter = (shape.side1 * 2) + (shape.side2 * 2);
}