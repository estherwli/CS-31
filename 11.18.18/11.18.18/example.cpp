#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
using namespace std;

/*
Pointers:
	-another way to implement passing-by-reference
	-traverse arrays
	-manipulate dynamic storage
	-represent relationships in data structures
*/

void polarToCartesian(double rho, double theta, double* xx, double* yy);

void main0() {
	double r;
	cin >> r;
	double angle;
	cin >> angle;
	double x;
	cin >> x;
	double y;
	cin >> y;
	polarToCartesian(r, angle, &x, &y); //&x means generate a pointer to x 
}

void polarToCartesian(double rho, double theta, double* xx, double* yy) {
	*xx = rho * cos(theta); //*xx means follow the pointer xx
	*yy = rho * sin(theta);
}

/*
double&		means		reference-to-double			or			another name for some double
double*		means		pointer-to-double			or			the-address-of-some-double
&x			means		generate a pointer to x		or			address of x
*p			means		follow the pointer p		or			the object that p points to
double a = 3.2;
double b = 5.1;
double* p = &a; //valid, p gets the pointer of a
double* q = 7.6; //INVALID
double d = p; //INVALID
double d = *p //valid, *p refers to the double that p points to
double& dd = d; //valid, dd is a reference not a pointer
p = b; //INVALID
p = &b; //valid, assigns one pointer to another (p gets the pointer of b)
*p = b; //valid, assigns one double to another (the object that p points to is now b)
*p += 4; //*p = *p + 4
int k = 7;
p = &k; //INVALID because &k generates a pointer to an INT, and p is a pointer to a DOUBLE
		//a pointer to an int cannot be converted to a pointer to a double
int* z = &k; //valid, z is an int pointer that now points to k
cout << (k * b); //valid, 2 doubles
cout << (k * p); //INVALID, can't multiply an int and a pointer
cout << (k * *p); //valid, double multiplied by the double that p points to
cout << (*z**p); //valid, the double that z points to multiplied by the double that p points to
double* q;
q = 4.7; //INVALID, undefined behavior because q is uninitialized
q = p; //valid, because p is a pointer to the double b
double* r = &a;
*r = b; //valid, the double that r points to is now b
if (p == r) //FALSE bc we are comparing the pointers' memory address (p points to b, r points to a), not the doubles they point to
if (p == q) //TRUE bc both point to the double b
if (*p == *r) //TRUE
const int MAXSIZE = 5;
double da[MAXSIZE];
int k;
double* dp;
for (k = 0; k < MAXSIZE; k				for (dp = &da[0]; dp < &da[MAXSIZE]; dp++)					for (dp = da; dp < da + MAXSIZE; dp++)
	da[k] = 3.6;							*dp = 3.6; //*(&da[0]) == da[0] bc *& cancel out			*dp = 3.6; //*(&da[0]) == da[0] bc *& cancel out
we assigned to dp the address of da[0] (may look like an integer, but not actually type int)
&da[MAXSIZE] is NOT out of bounds! it's a valid pointer but trying to follow that pointer leads to undefined behavior
dp++ is valid because:
	dp = dp + 1;
	dp = &da[0] + 1;
	dp = &da[0 + 1];
	dp = &da[1];
incrementing pointers:
&a[i] + j ==> &a[i + j];
&a[i] - j ==> &a[i - j];
NOTE: machine language translation for dp++ means add 8 bytes to the address that dp contains (but we don't need to use dp +=8; compiler does it)
comparing pointers:
&a[i] < &a[j] ==> i < j
NOTE: don't compare 2 pointers that point to different arrays (compiler picks addresses for each array)
a array pointer without an index points to the 0th element of an array:
a <==> &a[0]
&a[MAXSIZE] <==> a + MAXSIZE because:
	&a[5]
	&a[0 + 5]
	&a[0] + 5
	a + 5
********************pointer algebra summary**********************
*&x ==> x
&a[i] + j ==> &a[i + j]
&a[i] < &a[j] ==> i < j
a <==> &a[0]
p[i] ==> *(p + i)
&a[i] - &a[j] ==> i - j
*p = a[5] IS NOT THE SAME AS p = &a[5]
p->m ==> (*p).m
*****************************************************************
				 v same thing as const string a[]
int lookup(const string* a, int n, string target) {
	... a[k] ...
}
int main() {
	string sa[5] = { "cat", "mouse", "eel", "ferret", "horse" };
	int i = lookup(sa, 5, "eel");
	int j = lookup(&sa[0], 5, "eel");
	int m = lookup(sa + 1, 3, "ferret");
					^ same things as &sa[1]
}
*/

//USING A POINTER TO ITERATE THROUGH AN ARRAY
double* findFirstNegative(double a[], int n) {
	for (double* p = a; p < a + n; p++) { //a is the same thing as &a[0]
		if (*p < 0) //if the double that p points to is negative
			//return p - a //returns the element's position (function return type must be int)
			return p; //returns the pointer to the first negative element
	}
	//return a + n; //convention 1: return a pointer to n + 1 element of the array (1 after the interesting elements)
	return nullptr; //convention 2: return null pointer value (well-defined, but does not refer to anything)
}
/*
p = &a[0]
&a[2] == &a[0] + 2
&a[i] - &a[j] ==> i - j (compiler will take care of the /8 to account for 8 bytes per memory addresss)
&a[2] - &a[3] == -1
null pointer value
C++ 11: nullptr
C++ 11 and earlier: NULL //not the preferred style
******************everything you can do with nullptr******************
double* p = nullptr;
p = nullptr;
if (p == nullptr)
if (p != nullptr)
**********************************************************************
INVALID: *p ==> undefined behavior if p has the null pointer value
int* p1;
int* p2 = nullptr; //shows up as 0x00000000 if your program tries to follow a null pointer
... *p1 ... //INVALID bc undefined behavior p1 is uninitialized (may store random things --> program may or may not crash)
... *p2 ... //INVALID bc undefined behavior! p2 has the null pointer value (program will crash immediately)
*/

void main1() {
	double da[5];
	//...
	double* pfn = findFirstNegative(da, 5);
	//if (pfn == da + 5) //convention 1: checks if pointer points to the element after interesting elements
	if (pfn == nullptr) //convention 2: checks if pointer is a null pointer
		cout << "There are no negative values in the array" << endl;
	else {
		cout << "The first negative value is " << *pfn << endl; //*pfn prints the double that pfn points to
		cout << "It's at element number " << pfn - da << endl; //pfn is a pointer to an element in da; &da[i] - &da[0] = i
	}
}

struct Employee { //convention: capitalize first letter
	//data members/fields/instance variables/attributes: 
	string name;
	double salary;
	int age;
}; //DON'T FORGET THE SEMICOLON!!!

void printPaycheck(Employee e) {
	cout << "Pay to the order of " << e.name << " the amount $" << e.salary / 12 << endl;
}

void main2() {
	Employee e1;
	Employee e2;
	e1.name = "Fred";
	e1.salary = 60000;
	e1.age = 50;
	e1.age++;

	cout << "Enter a name: ";
	getline(cin, e2.name);

	Employee company[100]; //makes an array with 100 Employees
	company[3].name = "Ricky";
	int n = company[3].name.size();
	for (int k = 0; k < n; k++) //k < the size of the name string of the Employee object at position 3
		cout << company[3].name[k] << endl;

	int nEmployees = 0;
	//... read in some info, fill some of the array, set nEmployees

	printPaycheck(company[0]); //passed by value, makes a copy
}

/*
DOT OPERATOR
(an object of struct type).(the name of a data member of that type)
caller's object should not change:
	pass by value				==> best if objects are cheap to copy
	pass by const reference		==> best if objects are not cheap to copy
caller's object should change:
	pass by (non-const) referece
**********************************************************
-> OPERATOR
a pointer to						the name of a
an object of			->			member of that
some struct type					type
*/

/*
-member functions may be private, so only other member functions can call it
-constructors are called automatically when an object is created; not called w dot or -> operators
-const objects can only be called on by const member functions
-in C++ there is no difference between struct and class EXCEPT:
	members are public by default in struct
	members are private by default in class
-a collection of data with no interesting behavior --> use struct
-collection with interesting behavior --> use class
*/

class Target {
public:
	//constructor
	Target();

	//this following is the interface; implementation is done later
	bool move(char dir);
	int position() const; //const means this function promises not to modify the object it's called on
	void replayHistory() const;
	//void init(); is replaced by constructor to ensure private members are always initialized when Target is created

private:
	//Invariant:
	//	history contains only Rs and Ls
	//	pos == number of Rs in history minus number of Ls in history
	int pos;
	string history;
}; // <== don't forget semicolon!!!!!!

Target::Target() { //constructor has no return type 
	pos = 0;
	history = "";
}

bool Target::move(char dir) {
	switch (dir) {
	case 'R':
	case 'r':
		pos++;
		break;
	case 'L':
	case 'l':
		pos--;
		break;
	default:
		return false;
	}
	history += toupper(dir);
	return true;
}

int Target::position() const {
	return pos;
}

void Target::replayHistory() const {
	for (int i = 0; i < history.size(); i++) //not required to use -> operator in member functions 
		cout << history[i] << endl;
}

void repeatMove(Target& x, char dir, int nTimes) { //a non-member function
	for (int k = 0; k < nTimes; k++)
		x.move(dir); //doesn't need special permissions 
}

void f(const Target& x) {
	cout << x.position() << endl; //won't compile if position() is not a const member function
}

void movemain() {
	Target t;
	t.move('R');

	Target t2;
	t2.replayHistory();

	char ch;
	cin >> ch;
	if (!t.move(ch))
		//problem!

	//t.pos = 42; WON'T COMPILE bc pos is a private member

		repeatMove(t, 'R', 3);

	cout << t.position();
	//cout << t.pos; WON'T COMPILE bc main function has no permission to look at private member of t

	Target ta[3]; //implies constructor gets called as many times as there are elements in the array
	ta[0].move('L');
	ta[1].move('R');
	repeatMove(ta[2], 'L', 3);

}

/*
Data members should always be private
	-data member might be changed by other code without being known by class functions
	-changing implementation (deleting a data member) could make a function run faster but might break other code
	-exception: might be okay to use public data members if there is no constraints and no interesting functionality in the class


void f() {
	while (...)
		playGame();
}


-when you declare a NAMED local variable, it goes away after the program leaves the function
-when you declare a variable using NEW, it does not go away after the program leaves the function
	-objects declared with NEW only go away if you explicitly tell it to go away
-garbage: objects that were created but we no longer have access to
-dynamic allocation: allocation occurs during function execution; potential for garbage; keeps track of all the memory locations it's given out
-garbage collector: C++ may use a garbage collector to reclaim memory locations
-memory leak: not every allocation turns into garbage, but some do bc we forget to reclaim, so over time memory will run out
-dangling pointer: the object it points to has been deleted; pointer is not null, but trying to follow it is undefined behavior
*/

void addTargets(Target* ta[], int& nt, int howManyNewOnes) {
	//Target t; WRONG bc local variable does not exist outside the function

	for (int k = 0; k < howManyNewOnes; k++) {
		ta[nt] = new Target; //location doesn't have a name; only way to get to it is via the pointer; uses new location for each iteration
		nt++;

		/*
		Target t;
		ta[nt] = &t;
		nt++;
		WRONG bc t's scope does not exist outside the loop
		*/

	}
}

void playGame() {
	Target* targets[1000]; //left uninitialized 
	int nTargets = 0;

	if (1)
		addTargets(targets, nTargets, 3);
	int i;
	//... something gives i a value, say 1
	targets[i]->move('R');

	delete targets[1]; //trying to follow targets[1] is now undefined behavior; targets[1] is now a dangling pointer
	targets[1] = targets[2]; //targets[1] and targets[2] now point to the same object
	nTargets--;
	targets[2] = nullptr; //not necessary, but comforting to some
}

/*
class Person {
public:
	Person(string nm, int year);
	string name() const; //not allowed to name a member function the same as a data member
private:
	string m_name; //convention for data members: name_, m_name 
	int m_birthYear;
};

Person::Person(string nm, int year) {
	m_name = nm;
	m_birthYear = year;
}

string Person::name() const {
	return m_name;
}

Person p("Fred", 1999);

*/

bool a(int b) {
	b + 3;
	return true;
}

int main() {

}
