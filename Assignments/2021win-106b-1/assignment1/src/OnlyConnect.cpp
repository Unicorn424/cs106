/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"
#include "set.h"
using namespace std;

Set<char> constants = {'b', 'c', 'd', 'f', 'g', 'j', 'k', 'l', 'm', 'n',
                       'p', 'q', 's', 't', 'v', 'x', 'z', 'h', 'r', 'w', 'y'};

bool isConstant(const char ch) {
    if (constants.contains(ch)) {
        return true;
    }
    else {
        return false;
    }
}

/*
 * Function: onlyConnectizeHelper
 * ------------------------------------
 * The helper function will take a string as input and remove all characters except
 * constants and capitalize all constants in a recursive method.
 *
 * @param phrase: string waiting to be solved.
 * @param result: string being solved.
 *
 * Base case:
 *    when the first string goes to a string with length of 0.
 * Recursive body:
 * 1. get the first character and remove it from origin string.
 * 2. check if it is a constant ?
 *        capitalize it and put it at the end of result string
 *    else
 *        do nothing
 * 3. call helper function itself.
 */
void onlyConnectizeHelper(string& phrase, string& result) {
    if (phrase.size() != 0) {
        char ch = phrase[0];
        phrase = phrase.substr(1);
        if (isConstant(tolower(ch))) {
            result += toupper(ch);
        }

        onlyConnectizeHelper(phrase, result);
    }
}

string onlyConnectize(string phrase) {
    string result = "";
    onlyConnectizeHelper(phrase, result);

    return result;
}


/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */






