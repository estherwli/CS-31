#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);

int main() {
	string people[9] = { "rachel", "monica", "", "phoebe", "joey", "joey", "chandler", "ross", "janice" };
	assert(appendToAll(people, -2, "!!!") == -1); //invalid argument: negative elements of interest
	assert(appendToAll(people, 0, "!!!") == 0); //appends "!!!" to 0 elements of the array
	assert(appendToAll(people, 3, "!!!") == 3 && people[0] == "rachel!!!"
		&& people[1] == "monica!!!" && people[2] == "!!!"); //appends "!!!" to the first 2 elements of the array

	string friends[9] = { "rachel", "monica", "", "phoebe", "joey", "chandler", "ross", "ross", "janice" };

	assert(lookup(friends, -2, "rachel") == -1); //invalid argument: negative elements of interest
	assert(lookup(friends, 0, "rachel") == -1); //0 elements of interest
	assert(lookup(friends, 2, "monica") == 1); //looks up an item that exists in the first 2 elements of the array
	assert(lookup(friends, 9, "ross") == 6); //looks up an item that appears more than once in the array
	assert(lookup(friends, 2, "joey") == -1); //looks up an item that exists in the array but not in the elements specified
	assert(lookup(friends, 2, "gunther") == -1); //looks up an item that does not exist in the array

	string noFriends[1] = { "gunther" };
	string empty[5] = {};
	assert(positionOfMax(friends, -2) == -1); //invalid argument: negative elements of interest
	assert(positionOfMax(friends, 0) == -1); //0 elements of interest
	assert(positionOfMax(friends, 4) == 0); //looks for a max string that appears once in the first 4 elements of the array
	assert(positionOfMax(friends, 9) == 6); //looks for a max string that appears twice in the array
	assert(positionOfMax(noFriends, 1) == 0); //looks for a max string in an array with only 1 element
	assert(positionOfMax(empty, 5) == -1); //empty array with no elements of interest

	string office[6] = { "michael", "jim", "dwight", "pam", "toby", "angela" };
	assert(rotateLeft(office, -1, 0) == -1); //invalid argument: negative elements of interest
	assert(rotateLeft(office, 0, -1) == -1); //invalid argument: negative array element
	assert(rotateLeft(office, 6, 1) == 1 && office[0] == "michael" && office[1] == "dwight" && office[2] == "pam" && office[3] == "toby"
		&& office[4] == "angela" && office[5] == "jim"); //moves second element to last position, shifts every element after the second position left
	assert(rotateLeft(office, 0, 0) == 0 && office[0] == "michael"); //0 elements of interest
	assert(rotateLeft(office, 2, 0) == 0 && office[0] == "dwight" && office[1] == "michael"); //2 elements of interest

	string avengers[10] = { "ironman", "ironman", "thor", "captain", "hulk", "blackwidow", "ironman", "hawkeye", "hawkeye", "Hulk" };
	assert(countRuns(avengers, 0) == 0); //0 elements of interest
	assert(countRuns(avengers, -2) == -1); //invalid argument: negative elements of interest
	assert(countRuns(avengers, 1) == 1); //array with 1 element of interest
	assert(countRuns(avengers, 2) == 1); //array with a sequence of 2 consecutive identical items 
	assert(countRuns(avengers, 3) == 2);//array with 2 consecutive identical items followed by a different item
	assert(countRuns(avengers, 7) == 6); //array with 2 consecutive identical items followed by 4 different items, and an item identical to the first 2
	assert(countRuns(avengers, 10) == 8); //array of 10 elements with 2 sequences of 2 consecutive identical items

	/**************************************ASK ABOUT THIS BEFORE U TURN IT IN ***********************************************************************/


	/* assert(countRuns(empty, 5) == 0); //empty array with no elements of interest */

	cerr << "All tests passed.";
}


int appendToAll(string a[], int n, string value) {
	if (n < 0)
		return -1;
	for (int i = 0; i < n; i++) //iterates through each element of interest and appends value to each element
		a[i] += value;
	return n;
}

int lookup(const string a[], int n, string target) {
	for (int i = 0; i < n; i++) { //iterates through each element of interest and returns index of first element that matches target
		if (a[i] == target)
			return i;
	}
	return -1;
}

int positionOfMax(const string a[], int n) {
	string max = "";
	int index = -1;
	for (int i = 0; i < n; i++) { //iterates through each element of interest and compares it to the max string
		if (a[i] > max) {
			max = a[i]; //if current element > max string, it becomes the max string
			index = i; //stores index of max string
		}
	}
	return index;
}

int rotateLeft(string a[], int n, int pos) {
	if (n < 0 || pos < 0) //invalid arguments
		return -1;
	string temp = a[pos];
	int i;
	for (i = pos; i < n - 1; i++) //begins at pos, shift each element of interest 1 position to the left
		a[i] = a[i + 1];
	a[i] = temp;
	return pos;
}

int countRuns(const string a[], int n) {
	if (n < 0)
		return -1;
	if (n == 0)
		return 0;
	int count = 1; //first element always counts as a run
	for (int i = 1; i < n; i++) { //begins at position 1 to avoid bounds error in the if statement
		if (a[i] != a[i - 1]) //if next element is not identical to current element
			count++;
	}
	return count;
}

int flip(string a[], int n) {
	if (n < 0)
		return -1;
	for (int i = 0, j = n - 1; i < j; i++, j--) {
		string temp = a[i];


	}
}

