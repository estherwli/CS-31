#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype>
#include <cassert>
#include <cstring>
#include <cstdlib>
using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOC_LENGTH = 250;

void makeLowercase(char arr[][MAX_WORD_LENGTH + 1], int nPatterns);
void makeArray(const char document[], char doc[][MAX_DOC_LENGTH + 1]);
int makeProper(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns);
int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], const int separation[], int nPatterns);
void testMakeProper();
void testRate();

int d[3] = { 1,    0,    2 };
char w1[3][MAX_WORD_LENGTH + 1] = { "aa", "bb", "cc" };
char w2[3][MAX_WORD_LENGTH + 1] = { "dd", "ee", "ff" };

int e[2] = { 3,    3 };
char x1[2][MAX_WORD_LENGTH + 1] = { "aa", "cc" };
char x2[2][MAX_WORD_LENGTH + 1] = { "bb", "dd" };

const int THREE_LETTERS = 26 * 26 * 26;
int dd[THREE_LETTERS];
char ww1[THREE_LETTERS][MAX_WORD_LENGTH + 1];
char ww2[THREE_LETTERS][MAX_WORD_LENGTH + 1];

bool eq(int c, int dist, const char wd1[], const char wd2[])
{
	return d[c] == dist && strcmp(w1[c], wd1) == 0 &&
		strcmp(w2[c], wd2) == 0;
}

void testone(int n)
{
	switch (n)
	{
	case  1: {
		assert(makeProper(w1, w2, d, 0) == 0);
	} break; case  2: {
		assert(makeProper(w1, w2, d, 1) == 1 &&
			eq(0, 1, "aa", "dd"));
	} break; case  3: {
		d[0] = -1;
		assert(makeProper(w1, w2, d, 1) == 0);
	} break; case  4: {
		d[0] = -1;
		assert(makeProper(w1, w2, d, 2) == 1 &&
			eq(0, 0, "bb", "ee"));
	} break; case  5: {
		d[1] = -1;
		assert(makeProper(w1, w2, d, 2) == 1 &&
			eq(0, 1, "aa", "dd"));
	} break; case  6: {
		d[1] = -1;
		d[2] = -1;
		assert(makeProper(w1, w2, d, 3) == 1 &&
			eq(0, 1, "aa", "dd"));
	} break; case  7: {
		d[0] = -1;
		d[1] = -1;
		assert(makeProper(w1, w2, d, 3) == 1 &&
			eq(0, 2, "cc", "ff"));
	} break; case  8: {
		d[0] = -1;
		d[1] = -1;
		d[2] = -1;
		assert(makeProper(w1, w2, d, 3) == 0);
	} break; case  9: {
		strcpy(w1[1], "");
		assert(makeProper(w1, w2, d, 3) == 2 &&
			((eq(0, 1, "aa", "dd") && eq(1, 2, "cc", "ff")) ||
			(eq(1, 1, "aa", "dd") && eq(0, 2, "cc", "ff"))
				)
		);
	} break; case 10: {
		strcpy(w2[1], "");
		assert(makeProper(w1, w2, d, 3) == 2 &&
			((eq(0, 1, "aa", "dd") && eq(1, 2, "cc", "ff")) ||
			(eq(1, 1, "aa", "dd") && eq(0, 2, "cc", "ff"))
				)
		);
	} break; case 11: {
		strcpy(w1[1], "bb@");
		assert(makeProper(w1, w2, d, 3) == 2 &&
			((eq(0, 1, "aa", "dd") && eq(1, 2, "cc", "ff")) ||
			(eq(1, 1, "aa", "dd") && eq(0, 2, "cc", "ff"))
				)
		);
	} break; case 12: {
		strcpy(w1[1], "bb ");
		assert(makeProper(w1, w2, d, 3) == 2 &&
			((eq(0, 1, "aa", "dd") && eq(1, 2, "cc", "ff")) ||
			(eq(1, 1, "aa", "dd") && eq(0, 2, "cc", "ff"))
				)
		);
	} break; case 13: {
		strcpy(w1[1], "bBBb");
		assert(makeProper(w1, w2, d, 2) == 2 &&
			((eq(0, 1, "aa", "dd") && eq(1, 0, "bbbb", "ee")) ||
			(eq(1, 1, "aa", "dd") && eq(0, 0, "bbbb", "ee"))
				)
		);
	} break; case 14: {
		strcpy(w1[1], "bBBb");
		strcpy(w2[1], "EeEeE");
		assert(makeProper(w1, w2, d, 2) == 2 &&
			((eq(0, 1, "aa", "dd") && eq(1, 0, "bbbb", "eeeee")) ||
			(eq(1, 1, "aa", "dd") && eq(0, 0, "bbbb", "eeeee"))
				)
		);
	} break; case 15: {
		strcpy(w2[1], "bb");
		assert(makeProper(w1, w2, d, 2) == 2 &&
			((eq(0, 1, "aa", "dd") && eq(1, 0, "bb", "bb")) ||
			(eq(1, 1, "aa", "dd") && eq(0, 0, "bb", "bb"))
				)
		);
	} break; case 16: {
		strcpy(w2[0], "aa");
		strcpy(w1[1], "aa");
		strcpy(w2[1], "aa");
		assert(makeProper(w1, w2, d, 2) == 1 &&
			eq(0, 1, "aa", "aa")
		);
	} break; case 17: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		assert(makeProper(w1, w2, d, 3) == 2 &&
			((eq(0, 1, "aa", "dd") && eq(1, 2, "cc", "ff")) ||
			(eq(1, 1, "aa", "dd") && eq(0, 2, "cc", "ff"))
				)
		);
	} break; case 18: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		d[1] = 1;
		assert(makeProper(w1, w2, d, 3) == 2 &&
			((eq(0, 1, "aa", "dd") && eq(1, 2, "cc", "ff")) ||
			(eq(1, 1, "aa", "dd") && eq(0, 2, "cc", "ff"))
				)
		);
	} break; case 19: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		d[1] = 4;
		assert(makeProper(w1, w2, d, 3) == 2 &&
			((eq(0, 4, "aa", "dd") && eq(1, 2, "cc", "ff")) ||
			(eq(1, 4, "aa", "dd") && eq(0, 2, "cc", "ff"))
				)
		);
	} break; case 20: {
		strcpy(w1[1], "aa");
		strcpy(w2[1], "dd");
		strcpy(w1[2], "aa");
		strcpy(w2[2], "dd");
		assert(makeProper(w1, w2, d, 3) == 1 &&
			eq(0, 2, "aa", "dd")
		);
	} break; case 21: {
		strcpy(w1[2], "aa");
		strcpy(w2[2], "dd");
		d[1] = -1;
		assert(makeProper(w1, w2, d, 3) == 1 &&
			eq(0, 2, "aa", "dd")
		);
	} break; case 22: {
		strcpy(w1[1], "abcdefghijklmnopqrst");
		strcpy(w2[1], "abcdefghijklmnopqrsu");
		d[0] = -1;
		assert(makeProper(w1, w2, d, 2) == 1 &&
			eq(0, 0, "abcdefghijklmnopqrst",
				"abcdefghijklmnopqrsu")
		);
	} break; case 23: {
		strcpy(w2[0], "DD");
		strcpy(w1[1], "AA");
		strcpy(w2[1], "dD");
		assert(makeProper(w1, w2, d, 3) == 2 &&
			((eq(0, 1, "aa", "dd") && eq(1, 2, "cc", "ff")) ||
			(eq(1, 1, "aa", "dd") && eq(0, 2, "cc", "ff"))
				)
		);
	} break; case 24: {
		strcpy(w1[1], "dd");
		strcpy(w2[1], "aa");
		assert(makeProper(w1, w2, d, 3) == 2 &&
			((eq(0, 1, "aa", "dd") && eq(1, 2, "cc", "ff")) ||
			(eq(1, 1, "aa", "dd") && eq(0, 2, "cc", "ff"))
				)
		);
	} break; case 25: {
		strcpy(w1[1], "dd");
		strcpy(w2[1], "aa");
		d[1] = 1;
		assert(makeProper(w1, w2, d, 3) == 2 &&
			(((eq(0, 1, "aa", "dd") || eq(0, 1, "dd", "aa")
				) && eq(1, 2, "cc", "ff")
				) ||
				((eq(1, 1, "aa", "dd") || eq(1, 1, "dd", "aa")
					) && eq(0, 2, "cc", "ff")
					)
				)
		);
	} break; case 26: {
		strcpy(w1[1], "Dd");
		strcpy(w2[1], "aA");
		assert(makeProper(w1, w2, d, 3) == 2 &&
			((eq(0, 1, "aa", "dd") && eq(1, 2, "cc", "ff")) ||
			(eq(1, 1, "aa", "dd") && eq(0, 2, "cc", "ff"))
				)
		);
	} break; case 27: {
		int dx[7] = { 1, 3, 0, 2, 1, 0, 12 };
		char w1x[7][MAX_WORD_LENGTH + 1] = { "mad", "deranged",
			"NEFARIOUS", "half-witted", "robot", "plot", "have" };
		char w2x[7][MAX_WORD_LENGTH + 1] = { "scientist", "robot",
			"PLOT", "assistant", "deranged", "Nefarious", "mad" };
		assert(makeProper(w1x, w2x, dx, 7) == 4);
	} break; case 28: {
		assert(rate("", x1, x2, e, 2) == 0);
	} break; case 29: {
		assert(rate(" ", x1, x2, e, 2) == 0);
	} break; case 30: {
		assert(rate("aa bb", x1, x2, e, 2) == 1);
	} break; case 31: {
		e[0] = 0;
		assert(rate("aa bb", x1, x2, e, 2) == 1);
	} break; case 32: {
		e[0] = 0;
		assert(rate("aa     bb", x1, x2, e, 2) == 1);
	} break; case 33: {
		assert(rate(" aa bb", x1, x2, e, 2) == 1);
	} break; case 34: {
		assert(rate("aa bb ", x1, x2, e, 2) == 1);
	} break; case 35: {
		assert(rate("aa bb cc dd xx", x1, x2, e, 2) == 2);
	} break; case 36: {
		assert(rate("aa bb cc dd xx", x1, x2, e, 1) == 1);
	} break; case 37: {
		assert(rate("aa xx cc bb xx dd xx", x1, x2, e, 2) == 2);
	} break; case 38: {
		assert(rate("xx dd bb cc aa xx", x1, x2, e, 2) == 2);
	} break; case 39: {
		assert(rate("aa xx xx xx bb cc dd xx", x1, x2, e, 2) == 2);
	} break; case 40: {
		assert(rate("aa xx xx xx xx bb cc dd xx", x1, x2, e, 2) == 1);
	} break; case 41: {
		e[0] = 0;
		e[1] = 0;
		assert(rate("aa xx bb cc dd xx", x1, x2, e, 2) == 1);
	} break; case 42: {
		e[0] = 1;
		e[1] = 1;
		assert(rate("aa cc bb dd xx", x1, x2, e, 2) == 2);
	} break; case 43: {
		assert(rate("aa bb aa bb cc dd xx", x1, x2, e, 2) == 2);
	} break; case 44: {
		assert(rate("aa aa bb bb cc dd xx", x1, x2, e, 2) == 2);
	} break; case 45: {
		strcpy(x2[0], "aa");
		assert(rate("aa xx xx aa", x1, x2, e, 2) == 1);
	} break; case 46: {
		strcpy(x2[0], "aa");
		assert(rate("xx aa xx", x1, x2, e, 2) == 0);
	} break; case 47: {
		assert(rate("aA bb cc dd xx", x1, x2, e, 2) == 2);
	} break; case 48: {
		assert(rate("aa @@ ## $$ %% ^^ bb cc dd xx", x1, x2, e, 2) == 2);
	} break; case 49: {
		assert(rate("aa b@@b cc dd xx", x1, x2, e, 2) == 2);
	} break; case 50: {
		assert(rate("aa b123456789012345678901234567890b cc dd xx", x1, x2, e, 2) == 2);
	} break; case 51: {
		e[0] = 0;
		assert(rate("aa abcdefghijklmnopqrstuvwxyz bb cc dd xx", x1, x2, e, 2) == 1);
	} break; case 52: {
		e[0] = 1;
		assert(rate("aa abcdefghijklmnopqrstuvwxyz bb cc dd xx", x1, x2, e, 2) == 2);
	} break; case 53: {
		strcpy(x1[0], "abcdefghijklmnopqrst");
		assert(rate("abcdefghijklmnopqrst bb cc dd xx", x1, x2, e, 2) == 2);
	} break; case 54: {
		strcpy(x1[0], "abcdefghijklmnopqrst");
		assert(rate("abcdefghijklmnopqrstu bb cc dd xx", x1, x2, e, 2) == 1);
	} break; case 55: {
		assert(rate("aaa bb cc dd xx", x1, x2, e, 2) == 1);
	} break; case 56: {
		assert(rate("aa@bb cc dd xx", x1, x2, e, 2) == 1);
	} break; case 57: {
		assert(rate("aa bb@cc dd xx", x1, x2, e, 2) == 0);
	} break; case 58: {
		e[0] = 1000;
		assert(rate("xx aa xx", x1, x2, e, 2) == 0);
	} break; case 59: {
		strcpy(x1[0], "a");
		strcpy(x2[0], "b");
		e[0] = 123;
		char doc[250 + 1];
		strcpy(doc, "a ");
		for (int k = 0; k < 123; k++)
			strcpy(doc + 2 + 2 * k, "x ");
		strcpy(doc + 248, "b ");
		assert(rate(doc, x1, x2, e, 2) == 1);
	} break; case 60: {
		for (int k = 0; k < THREE_LETTERS; k++)
		{
			dd[k] = (k % 2) - 1;
			strcpy(ww1[k], "a");
			strcpy(ww2[k], "aaa");
			int kk = k;
			ww2[k][2] += kk % 26;
			kk /= 26;
			ww2[k][1] += kk % 26;
			kk /= 26;
			ww2[k][0] += kk;
		}
		assert(makeProper(ww1, ww2, dd, THREE_LETTERS) == THREE_LETTERS / 2);
		for (int k = 0; k < THREE_LETTERS / 2; k++)
			assert(dd[k] == 0 && strcmp(ww1[k], "a") == 0 &&
				islower(ww2[k][2]) &&
				(ww2[k][2] - 'a') % 2 == 1);
	} break; case 61: {
		for (int k = 0; k < THREE_LETTERS; k++)
		{
			dd[k] = 0;
			strcpy(ww1[k], "a");
			strcpy(ww2[k], "aaa");
			int kk = k;
			ww2[k][2] += kk % 26;
			kk /= 26;
			ww2[k][1] += kk % 26;
			kk /= 26;
			ww2[k][0] += kk;
		}
		assert(rate("a aaa a iaa a pzz a zzz", ww1, ww2, dd, THREE_LETTERS) == 4);
		assert(rate("a aaaa a iaaa a pzzz a zzzz", ww1, ww2, dd, THREE_LETTERS) == 0);
	} break;
	}
}

int main()
{
	cout << "Enter a test number (1 to 61): ";
	int n;
	cin >> n;
	if (n < 1 || n > 61)
	{
		cout << "Bad test number" << endl;
		return 1;
	}
	testone(n);
	cout << "Passed test " << n << endl;
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
	int separation2[] = { 1, 0, 2, 100 };
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
	assert(rate("doo          doo", word1, word2, s2, 5) == 1); //document contains 2 words separated by multiple spaces
	assert(rate("doo 28DOO", word1, word2, s2, 5) == 1); //document contains 2 words separated by a space and numbers
	assert(rate("doo-doo", word1, word2, s2, 5) == 0); //document contains words connected by a hyphen
	assert(rate("! doo !& doo!", word1, word2, s2, 5) == 1); //document begins and ends with non-letter character 
	assert(rate("&&&", word1, word2, s2, 5) == 0); //document only contains non-letter characters
	assert(rate("", word1, word2, s2, 5) == 0); //document is an empty string
	assert(rate("doooooooooooooooooooooooo doo", word1, word2, s2, 5) == 0); //document has a word with over 20 characters
	assert(rate("doo                        doo", word1, word2, s2, 5) == 1); //document contains more than 20 spaces
}

void makeLowercase(char arr[][MAX_WORD_LENGTH + 1], int nPatterns) {
	for (int i = 0; i < nPatterns; i++) {
		for (int j = 0; arr[i][j] != '\0'; j++) {
			if (isalpha(arr[i][j]))
				arr[i][j] = tolower(arr[i][j]); //changes all letter characters to lowercase
		}
	}
}

void makeArray(const char document[], char doc[][MAX_DOC_LENGTH + 1]) {
	for (int i = 0; !isalpha(document[i]); i++) {
		if (document[i] == '\0')
			return;
	}
	for (int i = 0, j = 0; document[i] != '\0' && j < MAX_DOC_LENGTH; j++) {
		while (document[i] == ' ' || !(isalpha(document[i])))//skips to the next non-space character
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
	char doc[MAX_DOC_LENGTH + 1][MAX_DOC_LENGTH + 1] = { '\0' };
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