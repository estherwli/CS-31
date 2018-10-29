#include <iostream>
#include <string>
using namespace std;

int main()
{
	//collects and stores odometer information from customer
	cout << "Odometer at start: ";
	int start;
	cin >> start;
	cout << "Odometer at end: ";
	int end;
	cin >> end;

	//collects and stores the number of days customer used rental car
	cout << "Rental days: ";
	int days;
	cin >> days;
	cin.ignore(10000, '\n');

	//collects and stores customer's name
	cout << "Customer name: ";
	string name;
	getline(cin, name);

	//collects and stores car information from customer
	cout << "Luxury car? (y/n): ";
	string luxury;
	getline(cin, luxury);

	//collects and stores the month in which the customer rented the car
	cout << "Month (1=Jan, 2=Feb, etc.): ";
	int month;
	cin >> month;

	//creates variables to simplify future calculations
	double cost = 0;
	int miles = end - start;

	//determines base charge based on rental days and whether or not customer used luxury car
	if (luxury == "y")
		cost = 61.00 * days;
	else if (luxury == "n")
		cost = 33.00 * days;

	cout << "---" << endl;

	//error messages 
	if (start < 0) //starting odometer reading is negative
		cout << "The starting odometer reading must be nonnegative.";
	else if (start > end) //ending odometer reading is less than the starting reading
		cout << "The final odometer reading must be at least as large as the starting reading.";
	else if (days <= 0) //number of rental days is not positive
		cout << "The number of rental days must be positive.";
	else if (name == "") //an empty string was provided for the customer name
		cout << "You must enter a customer name.";
	else if (!(luxury == "y" || luxury == "n")) // luxury status is not y or n 
		cout << "You must enter y or n.";
	else if (!(month == 1 || month == 2 || month == 3 || month == 4 ||
		month == 5 || month == 6 || month == 7 || month == 8 ||
		month == 9 || month == 10 || month == 11 || month == 12)) //month is not an integer between 1 and 12 inclusive
		cout << "The month number must be in the range 1 through 12.";
	//input is valid 
	else
	{
		//calculates cost based on mileage
		if (miles > 400)
		{
			cost += (miles - 400) * 0.19; //determines cost of miles beyond 400 
			miles -= miles - 400; //subtracts the mileage whose cost was already accounted for and stores new value in miles
		}
		if (miles > 100) //determines cost of miles between 100 and 400 (non-inclusive)
		{
			if (!(month > 3 && month < 12)) //nested if-statements determine cost per mile in December to March
				cost += (miles - 100) * 0.27; //subtracts the mileage whose cost was already accounted for and stores new value in miles
			else
				cost += (miles - 100) * 0.21; //nested if-statements determine cost per mile in April to November
			miles -= miles - 100; //subtracts the mileage whose cost was already accounted for and stores new value in miles
		}
		if (miles <= 100 && miles > 0) //determines cost of the first 100 miles
			cost += miles * 0.27;

		cout << "The rental charge for " << name << " is $" << cost << endl;
	}
}