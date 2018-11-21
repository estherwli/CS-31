#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype>
#include <cassert>
#include <cstring>
using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOC_LENGTH = 250;

void makeLowercase(char arr[][MAX_WORD_LENGTH + 1], int nPatterns);
void makeArray(const char document[], char doc[][MAX_DOC_LENGTH + 1]);
int makeProper(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns);
int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], const int separation[], int nPatterns);
void testMakeProper();
void testRate();

int main() {
	testMakeProper();
	testRate();
	cout << "All tests succeeded" << endl;
}
void testMakeProper() {
	char first[][MAX_WORD_LENGTH + 1] = { "rachel", "monica", "Phoebe", "Chandler", "j0ey", "ross", "janice", "", "rachel", "green", "phoebe", "Geller" };
	char last[][MAX_WORD_LENGTH + 1] = { "green", "geller", "Buffet", "BING!", "tr1bb1an1", "geller", "", "", "green", "RACHEL", "buffet", "ross" };
	int separation[] = { 1, -2, 3, 4, 5, 2, 7, 0, 5, 0, 3, 2 };
	assert(makeProper(first, last, separation, -2) == 0); //nPatterns is less than 0
	assert(makeProper(first, last, separation, 0) == 0); //nPatterns is equal to 0
	assert(makeProper(first, last, separation, 2) == 1); //a pattern has a negative separation value
	assert(makeProper(first, last, separation, 4) == 2); //a pattern has 1 word containing characters that are not letters
	assert(makeProper(first, last, separation, 5) == 2); //a pattern has 2 words containing characters that are not letters
	assert(makeProper(first, last, separation, 7) == 3); //a pattern has 1 word containing no characters
	assert(makeProper(first, last, separation, 8) == 3); //a pattern has 2 words containing no characters
	assert(makeProper(first, last, separation, 9) == 3); //2 patterns have the same w1 and w2 values, but the later pattern has a greater separation value
	assert(makeProper(first, last, separation, 10) == 3); //2 patterns have the same w1 and w2 values, but the later pattern has a smaller separation value
	assert(makeProper(first, last, separation, 11) == 3); //2 patterns have the same w1 and w2 values, but they have the same separation value
	assert(makeProper(first, last, separation, 12) == 3); //2 patterns have the same w1 and w2 values in different order

	char office1[][MAX_WORD_LENGTH + 1] = { "Jim", "Pam", "Dwight", "MICHAEL" };
	char office2[][MAX_WORD_LENGTH + 1] = { "HALPERT", "beesly", "shRuTe", "scott" };
<<<<<<< HEAD
	int separation2[] = { 1, 0, 2, 100 };
=======
	int separation2[] = {1, 0, 2, 100};
>>>>>>> 2202f7ca769a16d4bf2a57494111a4ad067cc1c3
	assert(makeProper(office1, office2, separation2, 4) == 4); //all patterns are valid

	char pll1[][MAX_WORD_LENGTH + 1] = { "emily", "hannah", "marin", "aria", "montgomery" };
	char pll2[][MAX_WORD_LENGTH + 1] = { "field5", "marin", "marin", "montgomery", "hannah" };
	int separation3[] = { 1, 0, 2, 251,0 };
	assert(makeProper(pll1, pll2, separation3, 1) == 0); //0 valid patterns
	assert(makeProper(pll1, pll2, separation3, 3) == 2); //a pattern has the same w1 and w2 values
	assert(makeProper(pll1, pll2, separation3, 4) == 3); //a pattern has a separation value greater than maximum document length
	assert(makeProper(pll1, pll2, separation3, 5) == 4); //a pattern shares w1 with another pattern but shares w2 with a different pattern
}
void testRate() {
	char document1[MAX_DOC_LENGTH] = { "The traffic on the 405-North freeway is terrible! Right?" };
	char w1[10][MAX_WORD_LENGTH + 1] = { "traffic", "freeway", "north", "terrible", "right" };
	char w2[10][MAX_WORD_LENGTH + 1] = { "the", "the", "terrible", "freeway", "the" };
	int s[10] = { 0, 1, 1, 10, 5 };
	assert(rate(document1, w1, w2, s, -1) == 0); //nPatterns is less than 0
	assert(rate(document1, w1, w2, s, 0) == 0); //nPatterns is equal to 0
	assert(rate(document1, w1, w2, s, 1) == 1); //looking for an existing pattern with 0 word separation
	assert(rate(document1, w1, w2, s, 2) == 2); //looking for an existing pattern with 1 word separation
	assert(rate(document1, w1, w2, s, 3) == 2); //looking for a nonexisting pattern 
	assert(rate(document1, w1, w2, s, 4) == 3); //looking for an existing pattern with a separation value greater than number of words in document
	assert(rate(document1, w1, w2, s, 5) == 4); //looking for an existing pattern with 4 word separation

	char document2[MAX_DOC_LENGTH] = { "Baby shark! Doo d00 Doo doo~ dudu BABY SHARK" };
	char document3[MAX_DOC_LENGTH] = { "whale-sharks are cool sharks cool cool sharks" };
	char word1[10][MAX_WORD_LENGTH + 1] = { "baby", "baby", "doo", "shark", "sharks" };
	char word2[10][MAX_WORD_LENGTH + 1] = { "baby", "doo", "doo", "shark", "cool" };
	int s2[10] = { 0, 4, 0, 10, 2 };
	assert(rate(document2, word1, word2, s2, 2) == 1); //looking for a pattern that exists in more than 1 way in the document
	assert(rate(document2, word1, word2, s2, 3) == 2); //looking for a pattern that exists, but the words of interest contain non-letter characters
	assert(rate(document2, word1, word2, s2, 4) == 3); //looking for a pattern where w1 and w2 refer to the same word, and pattern does exist
	assert(rate(document2, word1, word2, s2, 1) == 0); //looking for a pattern where w1 and w2 refer to the same word, but pattern does not exist
	assert(rate(document3, word1, word2, s2, 4) == 0); //patterns do not exist because they only exist in a part of a word
	assert(rate(document3, word1, word2, s2, 5) == 1); //pattern exists in more than one way in the document
	assert(rate("doo", word1, word2, s2, 5) == 0); //document only contains 1 word
<<<<<<< HEAD
	assert(rate("doo          doo", word1, word2, s2, 5) == 1); //document contains 2 words separated by multiple spaces
	assert(rate("doo 28DOO", word1, word2, s2, 5) == 1); //document contains 2 words separated by a space and numbers
	assert(rate("doo-doo", word1, word2, s2, 5) == 0); //document contains words connected by a hyphen
	assert(rate("! doo !& doo!", word1, word2, s2, 5) == 1); //document begins and ends with non-letter character 
	assert(rate("&&&", word1, word2, s2, 5) == 0); //document only contains non-letter characters
	assert(rate("", word1, word2, s2, 5) == 0); //document is an empty string
	assert(rate("doooooooooooooooooooooooo doo", word1, word2, s2, 5) == 0); //document has a word with over 20 characters
	assert(rate("doo                        doo", word1, word2, s2, 5) == 1); //document contains more than 20 spaces
=======
	assert(rate("000", word1, word2, s2, 5) == 0); //document only contains non-letter characters
	assert(rate("", word1, word2, s2, 5) == 0); //document is an empty string
>>>>>>> 2202f7ca769a16d4bf2a57494111a4ad067cc1c3
}

void makeLowercase(char arr[][MAX_WORD_LENGTH + 1], int nPatterns) {
	for (int i = 0; i < nPatterns; i++) {
		for (int j = 0; arr[i][j] != '\0'; j++) {
			if (isalpha(arr[i][j]))
				arr[i][j] = tolower(arr[i][j]); //changes all letter characters to lowercase
		}
	}
}

<<<<<<< HEAD
void makeArray(const char document[], char doc[][MAX_DOC_LENGTH + 1]) {
	for (int i = 0; !isalpha(document[i]); i++) {
		if (document[i] == '\0')
			return;
	}
	for (int i = 0, j = 0; document[i] != '\0' && j < MAX_DOC_LENGTH; j++) {
		while (document[i] == ' ' || !(isalpha(document[i])))//skips to the next non-space character
=======
void makeArray(const char document[], char doc[][MAX_DOC_LENGTH]) {
	for (int i = 0, j = 0; document[i] != '\0' && j < MAX_DOC_LENGTH; j++) {
		while (document[i] == ' ')
>>>>>>> 2202f7ca769a16d4bf2a57494111a4ad067cc1c3
			i++;
		for (int k = 0; document[i] != '\0' && document[i] != ' ' && k < MAX_DOC_LENGTH; i++) {
			if (isalpha(document[i])) {
				doc[j][k] = tolower(document[i]); //makes document all lowercase
				k++;
			}
		}
	} 
}

int makeProper(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns) {
	if (nPatterns <= 0)
		return 0;
	makeLowercase(word1, nPatterns);
	makeLowercase(word2, nPatterns);
	for (int i = 0; i < nPatterns; i++) {
		//if a word in the pattern contains no characters
		if (word1[i][0] == '\0' || word2[i][0] == '\0') {
			separation[i] = -1; //marks this pattern as invalid
			continue;
		}
		//if a word in the pattern contains a non-letter character 
		for (int j = 0; word1[i][j] != '\0'; j++) {
			if (!isalpha(word1[i][j]))
				separation[i] = -1; //marks this pattern as invalid
		}
		for (int j = 0; word2[i][j] != '\0'; j++) {
			if (!isalpha(word2[i][j]))
				separation[i] = -1; //marks this pattern as invalid
		}
		//if two patterns have the same w1 and w2 values in either order, mark the pattern with the lesser separation value as invalid
		for (int k = i + 1; k < nPatterns; k++) {
			if ((strcmp(word1[i], word1[k]) == 0 && strcmp(word2[i], word2[k]) == 0) || (strcmp(word2[i], word1[k]) == 0 && strcmp(word1[i], word2[k]) == 0)) {
				if (separation[i] <= separation[k])
					separation[i] = -1; //mark the patter with lesser or equal separation as invalid
				else
					separation[k] = -1;
			}
		}
	}
	//rearranges all arrays so patterns with separation < 0 come after patterns with separation >= 0
	for (int i = 0; i < nPatterns; i++) {
		if (separation[i] < 0) {
			for (int j = i; j < nPatterns; j++) {
				if (separation[j] >= 0) {
					char temp1[MAX_WORD_LENGTH]; //swaps elements of word1 array
					strcpy(temp1, word1[i]);
					strcpy(word1[i], word1[j]);
					strcpy(word1[j], temp1);

					char temp2[MAX_WORD_LENGTH]; //swaps elements of word2 array
					strcpy(temp2, word2[i]);
					strcpy(word2[i], word2[j]);
					strcpy(word2[j], temp2);

					int temp3 = separation[i]; //swaps elements of separation array
					separation[i] = separation[j];
					separation[j] = temp3;
				}
			}
		}
	}
	for (int i = 0; i < nPatterns; i++) {
		if (separation[i] < 0) //looks for the first negative value (indicating the first invalid pattern) 
			return i;
	}
	return nPatterns;
}

int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], const int separation[], int nPatterns) {
	char doc[MAX_DOC_LENGTH + 1][MAX_DOC_LENGTH + 1] = {'\0'};
	int count = 0;
	makeArray(document, doc); //changes document into an array of C strings
	for (int i = 0; i < nPatterns; i++) {
		for (int j = 0; j < MAX_DOC_LENGTH; j++) {
			if (strcmp(word1[i], doc[j]) == 0) { //if word1 matches a word in the document
				int temp = count; //used later to check count
				for (int k = separation[i] + 1; k > 0; k--) { //finds the boundaries set by separation value
					if (j + k < MAX_DOC_LENGTH && strcmp(word2[i], doc[j + k]) == 0) { //if word2 comes after word1
						count++;
						break;
					}
					else if (j - k >= 0 && strcmp(word2[i], doc[j - k]) == 0) { //if word2 comes before word1
						count++;
						break;
					}

				}
				if (count != temp) //ensures count does not get incremented twice for the same pattern
					break;
			}

		}
	}
	return count;
}
