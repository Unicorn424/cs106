#include "permutation.h"
#include "testing/SimpleTest.h"
#include "set.h"
#include <sstream>

/*
 * Function: permutationHelper
 * ------------------------------------
 * This is a helper function which bridge the gap between the implementation
 * and desired usage of function.
 *
 * @param str: string of characters which have not been chosen
 * @param prefix: string of chosen characters
 * @param result: record all possible permutation
 *
 * The basic idea is:
 * 1. choose one possible character from 'str'.
 * 2. explore the permutation of the rest of characters.
 *
 * Base case: There is nothing to choose in 'str'
 *      record the permutation ('prefix') into the result
 * Recursion:
 *      choose one character from 'str'.
 *      remove chosen character from 'str'.
 *      expore the permutation of rest characters.
 */
void permutationHelper(string str, string prefix,
                       Vector<string>& result) {
    if (str.length() == 0) {
        result.add(prefix);
        return;
    }

    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        string rest = str.substr(0, i) + str.substr(i+1);
        permutationHelper(rest, prefix + ch, result);
    }

}

/*
 * Function: permutation
 * ------------------------------------
 * The function will return a vector with the permutation of 'str'
 *
 * ex> permutation('dog')
 *     dog dgo odg ogd gdo god
 */
Vector<string> permutaion(string str) {
    Vector<string> result;
    permutationHelper(str, "", result);

    return result;
}

// Trick: use static variable set as a filter to the result of permutation
void permutationHelperWithoutRep(string str, string prefix,
                       Vector<string>& result) {
    static Set<string> set;

    if (str.length() == 0) {
        if (!set.contains(prefix)) {
            set.add(prefix);
            result.add(prefix);
        }
        return;
    }

    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        string rest = str.substr(0, i) + str.substr(i+1);
        permutationHelperWithoutRep(rest, prefix + ch, result);
    }

}

Vector<string> permutationWithoutRep(string str) {
    Vector<string> result;
    permutationHelperWithoutRep(str, "", result);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */

PROVIDED_TEST("Test the validation of permutation:") {
    Vector<string> result = permutaion("dog");
    stringstream ss;
    ss << result;
    string output = ss.str();

    EXPECT_EQUAL(output, "{\"dog\", \"dgo\", \"odg\", \"ogd\", \"gdo\", \"god\"}");
}

PROVIDED_TEST("Test the validation of permutaionWithoutRep:") {
    Vector<string> result = permutationWithoutRep("dd");
    stringstream ss;
    ss << result;
    string output = ss.str();

    EXPECT_EQUAL(output, "{\"dd\"}");
}
