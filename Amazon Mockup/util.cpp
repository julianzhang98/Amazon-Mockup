#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
	// can consist of ascii characters [48, 57] and [65, 90] and [97, 122]

	// REMEMBER TO ADD OTHER CHARACTERS LIKE '+' AND '-'

	set<string> keyWords;

	int tempFirst = 0;
	int tempLength = 0;
	for (unsigned int i = 0; i < rawWords.length(); i++) {

		// assume punctuation is everything except the following
		bool number = ((int)rawWords[i] >= 48 && (int)rawWords[i] <= 57);
		bool upperCaseLetter = ((int)rawWords[i] >= 65 && (int)rawWords[i] <= 90);
		bool lowerCaseLetter = ((int)rawWords[i] >= 97 && (int)rawWords[i] <= 122);
		
		if (number || upperCaseLetter || lowerCaseLetter) { 
			tempLength++;
			continue;
		}

		// if it is a punctuation character
		if (tempLength >= 2) {
			keyWords.insert(convToLower(rawWords.substr(tempFirst, tempLength)));
		}
		tempLength = 0;
		tempFirst = i+1;
	}

	if (tempLength >= 2) { // should take out the last word
		keyWords.insert(convToLower(rawWords.substr(tempFirst, tempLength)));
	}

	return keyWords;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
