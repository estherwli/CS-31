#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

//*************************************
//  isValidUppercaseStateCode
//*************************************

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos  &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}

bool hasProperSyntax(string pollData);
int tallySeats(string pollData, char party, int& seatTally);

int main()
{
	assert(hasProperSyntax("")); //empty string
	assert(!hasProperSyntax(",")); //consists of only ','
	assert(hasProperSyntax("CA")); //consists of only a state code
	assert(hasProperSyntax("CT5D")); //has a number with 1 digit
	assert(hasProperSyntax("CT52D")); //has a number with 2 digits
	assert(!hasProperSyntax("CT150D")); //has a number with 3 digits
	assert(!hasProperSyntax("C5D")); //incorrect state code
	assert(!hasProperSyntax("CT5D,")); //ends with ','
	assert(!hasProperSyntax("CA,,NY")); //has 2 consecutive ','
	assert(!hasProperSyntax("CT5D.NY")); //replaces ',' with '.'
	assert(!hasProperSyntax("CT5DNY9R17D1I")); //missing ','
	assert(!hasProperSyntax("CT5D, NY9R")); //has a space 
	assert(hasProperSyntax("CT5d,CT5d")); //same state code appears more than once
	assert(hasProperSyntax("CT5A2V9M2G")); //has party codes other than 'd' 'r' and 'i'
	assert(!hasProperSyntax("CT5")); //missing party code
	assert(hasProperSyntax("CT5D2D4D")); //same party code appears more than once

	int seats; // so we can detect whether tallySeats sets seats
	assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0 && seats == 22);
	assert(tallySeats("CT", 'd', seats) == 0 && seats == 0);
	assert(tallySeats("CT5D", 'd', seats) == 0 && seats == 5); //has a number with 1 digit
	assert(tallySeats("CT50d", 'd', seats) == 0 && seats == 50); //has a number with 2 digits
	seats = -999;
	assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2 && seats == -999); //party is not a letter
	assert(tallySeats("CA12D,FL19R327D2I,OR,nd", 'R', seats) == 1 && seats == -999); //has a number with 3 digits
	assert(tallySeats("CA2DR,FL19R327D2I,OR,nd", 'R', seats) == 1 && seats == -999); //missing digits for party
	assert(tallySeats("CT5DNY9R17D1I,VT,ne3r00D", 'D', seats) == 1 && seats == -999); //missing ',' 
	assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'X', seats) == 0 && seats == 0); //party char is not found in pollData
	assert(tallySeats("NE2R,CA5R17D1I,ga13r05D", 'R', seats) == 0 && seats == 20);
	assert(tallySeats("", 'D', seats) == 0 && seats == 0); //empty string
	assert(tallySeats("LA01D,NY9R17D1I,VT,ne3r", 'D', seats) == 0 && seats == 18); //has a number with first digit 0
	assert(hasProperSyntax("MA9D,KS4R") && hasProperSyntax("KS4R,MA9D")); //reversed order of forecasts
	assert(hasProperSyntax("MA9D,,KS4R") == hasProperSyntax("KS4R,,MA9D")); //has 2 consecutive ','

	cerr << "All tests succeeded" << endl;
}

bool hasProperSyntax(string pollData)
{
	if (pollData == "") //checks if string is empty
		return true;
	if (!isalpha(pollData[pollData.size() - 1])) //last character must be a letter
		return false;
	for (int i = 0; i < pollData.size(); i++) //changes all letter to uppercase
		pollData[i] = toupper(pollData[i]);

	int index = 0;
	while (index < pollData.size()) {

		//checks if state code is valid
		string state = pollData.substr(index, 2);
		if (!isValidUppercaseStateCode(state))
			return false;
		index += 2;

		//checks everything following the state code up to ','
		while (index < pollData.size() && pollData[index] != ',') {
			int numOfDigits = 0;
			if (!isdigit(pollData[index]))
				return false;
			while (isdigit(pollData[index])) {
				numOfDigits++;
				index++;
			}
			if (numOfDigits > 2 || !isalpha(pollData[index])) //checks if >2 digits or number is not followed by a party code (ie !@#$%^&*)
				return false;
			else
				index++;
		}
		if (index < pollData.size()) //only increments index if not at last position yet
			index++;
	}
	return true;
}

int tallySeats(string pollData, char party, int& seatTally) {
	if (!hasProperSyntax(pollData))
		return 1;
	else if (!isalpha(party))
		return 2;
	else {
		//changes party and pollData to uppercase for easier comparison
		party = toupper(party);
		for (int i = 0; i < pollData.size(); i++)
			pollData[i] = toupper(pollData[i]);

		int i = pollData.size() - 1; //begins checking from last character
		seatTally = 0;
		while (i > 2) { //prevents undefined behavior from i being out-of-bounds
			if (pollData[i] == party) {
				int j = i - 1;
				while (!isalpha(pollData[j - 1])) {
					j--; //marks index of first digit
				}
				int add = atoi(pollData.substr(j, i - j).c_str()); //converts substring of digits to int
				seatTally += add; //updates the true value of seatTally
				i = j;
			}
			i--;
		}
	}
	return 0;
}