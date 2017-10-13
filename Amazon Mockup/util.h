#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates  
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> final;

	for (typename std::set<T>::const_iterator it = s1.begin(); it != s1.end(); ++it) {
		if (s2.find(*it) != s2.end()) {
			final.insert(*it); // only if it exists in both s1 and s2
		}
	}

	return final;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> final;

	for (typename std::set<T>::const_iterator it = s1.begin(); it != s1.end(); ++it) {
		final.insert(*it); // every element in the first set is unique so no check needed
	}
	for (typename std::set<T>::const_iterator it = s2.begin(); it != s2.end(); ++it) {
		if (final.find(*it) == final.end()) {
			// only if it doesn't exist in the set already
			final.insert(*it);
		}
		
	}

	return final;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) ;

// trim from end
std::string &rtrim(std::string &s) ;

// trim from both ends
std::string &trim(std::string &s) ;
#endif
