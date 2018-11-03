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
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);

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
	assert(countRuns(avengers, -2) == -1); //invalid argument: negative elements of interest
	assert(countRuns(avengers, 0) == 0); //0 elements of interest
	assert(countRuns(avengers, 1) == 1); //array with 1 element of interest
	assert(countRuns(avengers, 2) == 1); //array with a sequence of 2 consecutive identical items 
	assert(countRuns(avengers, 3) == 2);//array with 2 consecutive identical items followed by a different item
	assert(countRuns(avengers, 7) == 6); //array with 2 consecutive identical items followed by 4 different items, and an item identical to the first 2
	assert(countRuns(avengers, 10) == 8); //array of 10 elements with 2 sequences of 2 consecutive identical items

	/**************************************ASK ABOUT THIS BEFORE U TURN IT IN ***********************************************************************/


	/* assert(countRuns(empty, 5) == 0); //empty array with no elements of interest */

	string gossipGirl[5] = { "serena", "blair", "nate", "chuck", "dan" };
	string amigos[6] = { "rachel", "monica", "phoebe", "chandler", "joey", "ross" };
	assert(flip(gossipGirl, -1) == -1); //invalid argument: negative elements of interest
	assert(flip(gossipGirl, 0) == 0); //0 elements of interest
	assert(flip(gossipGirl, 1) == 1 && gossipGirl[0] == "serena"); //1 element of interest
	assert(flip(gossipGirl, 5) == 5 && gossipGirl[0] == "dan", "chuck", "nate", "blair", "serena"); //array with odd elements of interest
	assert(flip(amigos, 6) == 6 && amigos[0] == "ross" && amigos[1] == "joey" && amigos[2] == "chandler" && amigos[3] == "phoebe"
		&& amigos[4] == "monica" && amigos[5] == "rachel"); //array with even elements of interest
	assert(flip(noFriends, 1) == 1 && noFriends[0] == "gunther"); //array with only 1 element
	assert(flip(empty, 5) == 5); //empty array with no elements of interest

	string strange[5] = { "mike", "will", "dustin", "caleb", "eleven" };
	string stranger[6] = { "mike", "will", "dustin", "max", "caleb", "eleven" };
	assert(differ(strange, -2, stranger, 5) == -1); //invalid argument: one of the arrays has negative elements of interest
	assert(differ(strange, 4, stranger, -2) == -1); //invalid argument: one of the arrays has negative elements of interest
	assert(differ(strange, 0, stranger, 0) == 0); //0 elements of interest in both arrays
	assert(differ(strange, 0, stranger, 1) == 0); //0 elements of interest in one of the arrays
	assert(differ(strange, 1, stranger, 0) == 0); //0 elements of interest in one of the arrays
	assert(differ(strange, 1, stranger, 1) == 1); //2 arrays with 1 element of interest that do not differ
	assert(differ(strange, 2, stranger, 4) == 2); //1 array runs out before differing from the other array
	assert(differ(strange, 5, stranger, 6) == 3); //2 arrays of different sizes with differing elements

	string marvel[6] = { "drstrange", "quicksilver", "loki", "thanos", "killmonger", "scarletwitch" };
	string marvel2[8] = { "drstrange", "quicksilver", "loki", "thanos", "loki", "thanos", "killmonger", "scarletwitch" };
	string villains[3] = { "loki", "thanos", "killmonger" };
	assert(subsequence(marvel, -2, villains, 2) == -1); //invalid argument: one of the arrays has negative elements of interest
	assert(subsequence(marvel, 2, villains, -2) == -1); //invalid argument: one of the arrays has negative elements of interest
	assert(subsequence(marvel, 2, villains, 3) == -1); //n1 < n2, thus impossible to have subsequence a2 in a1
	assert(subsequence(marvel, 0, villains, 2) == -1); //0 elements of interest in a1, thus impossible to have subsequence a2 in a1
	assert(subsequence(marvel, 2, villains, 0) == 0); //0 elements of interest in a2; 0 elements is a subsequence of any sequence
	assert(subsequence(marvel, 6, villains, 3) == 2); //a2 subsequence is found in the elements of interest in a1
	assert(subsequence(marvel, 4, villains, 3) == -1); //a2 subsequence is not found in the elements of interest in a1
	assert(subsequence(marvel2, 8, villains, 3) == 4); //part of a2 is found in a1 before the entire a2 subsequence is found in a1

	string pokemon[10] = { "jolteon", "snorlax", "squirtle", "pikachu", "bulbasaur", "bulbasaur", "jigglypuff" };
	string eeveelutions[10] = { "glaceon", "flareon", "umbreon", "espeon", "vaporeon", "jolteon", "sylveon", "leafon" };
	string starter[10] = { "charmander", "bulbasaur", "squirtle" };
	assert(lookupAny(pokemon, -2, starter, 3) == -1); //invalid argument: one of the arrays has negative elements of interest
	assert(lookupAny(pokemon, 1, starter, -2) == -1); //invalid argument: one of the arrays has negative elements of interest
	assert(lookupAny(pokemon, 0, starter, 3) == -1); //0 elements of interest in a1, thus impossible to find an element that matches one in a2
	assert(lookupAny(pokemon, 3, starter, 3) == 2); //1 element in a2 is found in a1  
	assert(lookupAny(pokemon, 6, starter, 3) == 2);  //more than 1 element in a2 is found in a1, should return index of first match
	assert(lookupAny(pokemon, 6, starter, 2) == 4); //2 identical elements in a1 match an element in a2, should return index of first match
	assert(lookupAny(pokemon, 6, eeveelutions, 3) == -1); //1 element in a1 matches one element in a2, but is not within a2's elements of interest 
	assert(lookupAny(eeveelutions, 7, starter, 3) == -1); //0 elements in a1 match any element in a2

	string food[10] = { "bplate", "feast", "covel", "cafe1919", "bcafe", "rendevous", "thestudy" };
	assert(divide(food, -2, "feast") == -1); //invalid argument: negative elements of interest
	assert(divide(food, 0, "feast") == 0); //0 elements of interest
	assert(divide(food, 6, "westwood") == 6); //all elements in the array are < divider
	assert(divide(food, 6, "ackerman") == 0); //all elements in the array are not < divider
	assert(divide(food, 6, "bcafe") == 0); //array has one element that is not < divider
	assert(divide(food, 6, "feast") == 4); //divider has a match in the array, and array has more than one element that is not < divider
	assert(divide(food, 6, "deneve") == 4); //divider does not have a match in the array, but array has elements that are not < divider


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
		a[i] = a[j];
		a[j] = temp;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0)
		return -1;
	int index = 0;
	for (int i = 0, j = 0; i < n1 && j < n2; i++, j++) {
		if (a1[i] == a2[j])
			index++;
	}
	return index;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0 || n1 < n2)
		return -1;
	if (n2 == 0)
		return 0;
	int index = -1;
	for (int i = 0, j = 0; i < n1; i++) {
		if (a1[i] == a2[j]) {
			index = i;
			while (a1[i] == a2[j]) {
				if (j == n2 - 1)
					return index;
				if (i == n1 - 1)
					return -1;
				i++;
				j++;
			}
			i--;
		}
		j = 0;
		index = -1;
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0)
		return -1;
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			if (a1[i] == a2[j])
				return i;
		}
	}
	return -1;
}

int divide(string a[], int n, string divider) {
	if (n < 0)
		return -1;
	for (int i = 0; i < n; i++) {
		if (a[i] >= divider) {
			for (int j = i; j < n; j++) {
				if (a[j] < divider) {
					string temp = a[i];
					a[i] = a[j];
					a[j] = temp;
				}
			}
		}  
	}
	for (int i = 0; i < n; i++) {
		if (a[i] >= divider)
			return i;
	}
	return n;
}






