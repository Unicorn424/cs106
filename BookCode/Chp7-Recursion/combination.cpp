#include "combination.h"
#include "testing/SimpleTest.h"
#include <sstream>
#include "set.h"

/*
 * Function: combinationHelper
 * ------------------------------------
 * This is a helper function to bridge the gap between implementation and API.
 * combinationHelper will enumerate all possible combination of the given string.
 *
 * @param str: the string to be treated. (unsolved)
 * @param prefix: the string of chosen characters.
 * @param result: records possible combinations.
 *
 * The basic idea is to traverse string from left to right. The decision will be made
 * on each character (choose or not).
 *
 * Base case:
 *      There is no character left in 'str'.
 * Recursion:
 *      select the first character and remove it from 'str'.
 *      put it into 'prefix' or not. (two possible).
 *      solve the rest character recursively.
 */
void combinationHelper(string str, string prefix,
                       Vector<string>& result) {
    if (str.length() == 0) {
        result.add(prefix);
        return;
    }

    char ch = str[0];
    str = str.substr(1);
    combinationHelper(str, prefix + ch, result); // choose
    combinationHelper(str, prefix, result);      // not choose
}

/*
 * Function: combination
 * ------------------------------------
 * The function will return the combination of the given string.
 *
 * ex> the combination of "abc"
 *     'abc' 'ab' 'ac' 'bc' 'a' 'b' 'c' ''
 *
 * Notice:
 *     permutation: a(n, k) = n! / k!
 *     combination: c(n, k) = n! / k!(n-k)!
 */
Vector<string> combination(string str) {
    Vector<string> result;
    combinationHelper(str, "", result);

    return result;
}

void combinationHelperWithoutRep(string str, string prefix,
                       Vector<string>& result) {
    static Set<string> filter;

    if (str.length() == 0) {
        if (!filter.contains(prefix)) {
            filter.add(prefix);
            result.add(prefix);
        }
        return;
    }

    char ch = str[0];
    str = str.substr(1);
    combinationHelperWithoutRep(str, prefix + ch, result); // choose
    combinationHelperWithoutRep(str, prefix, result);      // not choose
}


Vector<string> combinationWithoutRep(string str) {
    Vector<string> result;
    combinationHelperWithoutRep(str, "", result);

    return result;
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */

PROVIDED_TEST("Test the validation of combination:") {
    Vector<string> result = combination("abc");
    stringstream ss;
    ss << result;
    string output = ss.str();

    EXPECT_EQUAL(output, "{\"abc\", \"ab\", \"ac\", \"a\", \"bc\", \"b\", \"c\", \"\"}");
}

PROVIDED_TEST("Test the validation of combinationWithoutRep:") {
    Vector<string> result = combinationWithoutRep("aaa");
    stringstream ss;
    ss << result;
    string output = ss.str();

    EXPECT_EQUAL(output, "{\"aaa\", \"aa\", \"a\", \"\"}");
}
