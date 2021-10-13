#include "standardlibrary.h"
#include "testing/SimpleTest.h"
#include <cctype>
#include "strlib.h"
using namespace std;

void unknown() {
    string str1 = "Aaaa";
    string str2 = "Bbbb";
    string str3 = "aAAA";
    string str4 = "bBBB";

    auto result = str1 < str2;
    cout << result << endl;

    result = str1 > str3;
    cout << result << endl;

    // c++ string to c string
    string cstr = str1.c_str();
    cout << string(4, 'a') << endl;
}

/* *******************************
 *          <string>
 * - str.length, str.substr
 * - str.find, str.erase, str.insert
 * - str.replace, str.c_str
 * *******************************/

bool myStartsWith(string str, string prefix) {
    if (prefix.length() > str.length()) {
        return false;
    }

    for (int i = 0; i < prefix.length(); i++) {
        if (str[i] != prefix[i]) {
            return false;
        }
    }

    return true;
}

void reverseInPlace(string& str) {
    int last = str.length() - 1;
    for (int i = 0; i < str.length() / 2; i++) {
        swap(str[i], str[last-i]);
    }
}


/* *******************************
 *          <cctype>
 * - isalpha, isdigit, isupper ...
 * - toupper, tolower
 * *******************************/

bool myEqualsIgnoreCase(string lstr, string rstr) {
    if (lstr.length() != rstr.length()) {
        return false;
    }

    for (int i = 0; i < lstr.length(); i++) {
        if (tolower(lstr[i]) != tolower(rstr[i])) {
            return false;
        }
    }

    return true;
}

/* ****************************** *
 *         Application
 * ****************************** */

bool isPalindrome(string str) {
    string str_reversed = str;
    reverseInPlace(str_reversed);

    if (str == str_reversed) {
        return true;
    }
    else {
        return false;
    }
}

string myTrimBegin(string str) {
    while (str[0] == ' ') {
        str = str.substr(1);
    }

    return str;
}

string myTrimEnd(string str) {
    int last = str.length() - 1;
    while (str[last--] == ' ') {
        str = str.substr(0, str.length() - 1);
    }

    return str;
}

string myTrim(string str) {
    string result = myTrimBegin(str);
    result = myTrimEnd(result);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */

PROVIDED_TEST("Test for strlib.h function") {
    EXPECT_EQUAL(stringToInteger("12"), 12);
    EXPECT_EQUAL(toUpperCase("Husky"), "HUSKY");
    EXPECT_EQUAL(trim("  a a  "), "a a");
}

PROVIDED_TEST("Test for standard library functions:") {
    string str1 = "hello";
    string str2 = " world";
    string result = str1 + str2;
    EXPECT_EQUAL(result, "hello world");

    string str3("fancy");
    str3 += str2;
    EXPECT_EQUAL(str3, "fancy world");

    EXPECT_EQUAL(str2.substr(1), "world");
    EXPECT_EQUAL(str3.find("an"), 1);
    EXPECT_EQUAL(str3.erase(1, 2), "fcy world");
}

PROVIDED_TEST("Test the validation of startsWith:") {
    string str = "ccccccc";
    EXPECT(myStartsWith(str, "c"));
    EXPECT(myStartsWith(str, ""));
    EXPECT(!myStartsWith(str, "a"));
    EXPECT(!myStartsWith(str, "aaaaaaaaaa"));
}

PROVIDED_TEST("Test the validation of str_reverse:") {
    string empty_str = "";
    reverseInPlace(empty_str);
    EXPECT_EQUAL(empty_str, "");

    string str = "hello";
    reverseInPlace(str);
    EXPECT_EQUAL(str, "olleh");

    str = "a";
    reverseInPlace(str);
    EXPECT_EQUAL(str, "a");
}

PROVIDED_TEST("Test the function equalsIgnoreCase:") {
    string str1 = "";
    string str2 = "";
    EXPECT(myEqualsIgnoreCase(str1, str2));

    string str3 = "HusKY";
    string str4 = "HUskY";
    EXPECT(myEqualsIgnoreCase(str3, str4));

    string str5 = "Dwog";
    string str6 = "dWOO";
    EXPECT(!myEqualsIgnoreCase(str5, str6));
}

PROVIDED_TEST("Test for isPanlindrome:") {
    EXPECT(isPalindrome(""));
    EXPECT(!isPalindrome("Hello"));
    EXPECT(isPalindrome("aba"));
}

PROVIDED_TEST("Test for Trim functions") {
    string str = "   aa   ";
    EXPECT_EQUAL(myTrimBegin(str), "aa   ");
    EXPECT_EQUAL(myTrimEnd(str), "   aa");
    EXPECT_EQUAL(myTrim(str), "aa");

    string str_empty = "";
    EXPECT_EQUAL(myTrimBegin(str_empty), "");
    EXPECT_EQUAL(myTrimEnd(str_empty), "");
    EXPECT_EQUAL(myTrim(str_empty), "");

    string str_blank = "      ";
    EXPECT_EQUAL(myTrimBegin(str_blank), "");
    EXPECT_EQUAL(myTrimEnd(str_blank), "");
    EXPECT_EQUAL(myTrim(str_blank), "");
}

