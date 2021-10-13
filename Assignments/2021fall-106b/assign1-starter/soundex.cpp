/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include "map.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
using namespace std;

/* This function takes a string s and returns a version of
 * the string that has all non-letter characters removed
 * from it.
 *
 * WARNING: The provided code is buggy!
 *
 * Use unit tests to identify which inputs to this function
 * are incorrectly handled. Then, remove this comment and
 * replace it with a description of the bug you fixed.
 */

// s = '98765'
//      01234
// s = '8765'
//      0123

string removeNonLetters(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (!isalpha(s[i])) {
            // remove the character at index i
            s = s.substr(0,i) + s.substr(i+1);
        }
    }

    return s;
}

string removeNonLettersFixed(string s) {
    for (int i = 0; i < s.length();) {
        if (!isalpha(s[i])) {
            // remove the character at index i
            s = s.substr(0,i) + s.substr(i+1);
        }
        else {
            i++;
        }
    }

    return s;
}

/* This function will encode each letter of input string as a digit using
 * following rules:
 * 1. 0: A E I O U H W Y
 * 2. 1: B F P V
 * 3. 2: C G J K Q S X Z
 * 4. 3: D T
 * 5. 4: L
 * 6. 5: M N
 * 7. 6: R
 */
string encoder(string s) {
    // construct a mapping table
    Map<char, char> toDigit;
    toDigit['A'] = toDigit['E'] = toDigit['I']= toDigit['O'] = toDigit['U'] =
    toDigit['H'] = toDigit['W'] = toDigit['Y'] = '0';
    toDigit['B'] = toDigit['F'] = toDigit['P']= toDigit['V'] = '1';
    toDigit['C'] = toDigit['G'] = toDigit['J']= toDigit['K'] = toDigit['Q'] =
    toDigit['S'] = toDigit['X'] = toDigit['Z'] = '2';
    toDigit['D'] = toDigit['T'] = '3';
    toDigit['L'] = '4';
    toDigit['M'] = toDigit['N'] = '5';
    toDigit['R'] = '6';

    string s_encoded("");

    for (char ch : s) {
        s_encoded += toDigit[toupper(ch)];
    }

    return s_encoded;
}

/* This function will coalesce adjacent duplicate digit from the input string.
 */
string removeAdjacentDuplicateLetters(string s) {
    if (s == "") {
        return "";
    }

    if (s.size() == 1) {
        return s;
    }

    for (int i = 1; i < s.length();) {
        if (s[i] == s[i-1]) {
            s = s.substr(0, i) + s.substr(i+1);
        }
        else {
            i++;
        }
    }

    return s;
}

string replaceTheFirstDigit(string s, char first) {
    s[0] = toupper(first);

    return s;
}

string removeAllZeros(string s) {
    string result("");

    for (char ch : s) {
        if (ch != '0') {
            result += ch;
        }
    }

    return result;
}

string formatIntoLength4(string s) {
    if (s.length() >= 4) {
        return s.substr(0, 4);
    }
    else {
        string result(4, '0');
        for (int i = 0; i < s.length(); i++) {
            result[i] = s[i];
        }
        return result;
    }
}

/* This function takes a string as input and return soundex code of it.
 */
string soundex(string s) {
    // remove all non-digit letter
    char first = s[0];

    s = removeNonLettersFixed(s);
    s = encoder(s);
    s = removeAdjacentDuplicateLetters(s);
    s = replaceTheFirstDigit(s, first);
    s = removeAllZeros(s);
    s = formatIntoLength4(s);

    return s;
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames

    /* TODO: Fill in the remainder of this function. */
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}

STUDENT_TEST("Ignored cases by removeNonLetters") {
    string s = "tl  dr";
    string result = removeNonLettersFixed(s);
    EXPECT_EQUAL(result, "tldr");
    s = "";
    result = removeNonLettersFixed(s);
    EXPECT_EQUAL(result, "");
    s = "98765";
    result = removeNonLettersFixed(s);
    EXPECT_EQUAL(result, "");
}

STUDENT_TEST("Test for encode a letter string to a digit string") {
    EXPECT_EQUAL(encoder("Curie"), "20600");
    EXPECT_EQUAL(encoder(""), "");
    EXPECT_EQUAL(encoder("CCCC"), "2222");
    EXPECT_EQUAL(encoder("OConner"), "0205506");
}

STUDENT_TEST("Test for remove adjacent duplicate digits") {
    EXPECT_EQUAL(removeAdjacentDuplicateLetters(""), "");
    EXPECT_EQUAL(removeAdjacentDuplicateLetters("1"), "1");
    EXPECT_EQUAL(removeAdjacentDuplicateLetters("2222"), "2");
    EXPECT_EQUAL(removeAdjacentDuplicateLetters("0205506"), "020506");
}

PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here


