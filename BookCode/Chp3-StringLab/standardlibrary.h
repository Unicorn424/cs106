#ifndef STANDARDLIBRARY_H
#define STANDARDLIBRARY_H

#include <string>

/* In this part, we will implement some useful function with c++
 * standard library <string.h>.
 */

void unknown();

bool myStartsWith(std::string str, std::string prefix);
void reverseInPlace(std::string& str);
bool myEqualsIgnoreCase(std::string lstr, std::string rstr);
bool isPalindrome(std::string str);
std::string myTrimBegin(std::string str);
std::string myTrimEnd(std::string str);
std::string myTrim(std::string str);

#endif // STANDARDLIBRARY_H
