#include "calculation.h"
#include "error.h"
#include "testing/SimpleTest.h"

/*
 * Function: calcHelper
 * ------------------------------------
 * The helper function is taking care of how the algorithm is implemented. It will
 * add 'index' to track where i am.
 *
 * @param exp: the expression to calculate
 * @param index: indicate where we are
 *
 * Observation:
 * - single digit is simplest, like '0'
 * - simulate simplest expression with an operator, like '(1+1)'. If this works, then
 * every combination of single expression will work.
 *
 * Similarity: exp = (operand + operator + operand)
 *
 * Base case:
 *      only digit in expression
 * Recursion:
 *      1. skip when encountering '('.
 *      2. calculate left operand.
 *      3. save operator.
 *      4. calculate right operand.
 *      5. skip when encountering ')'.
 *      6. return final calculation.
 *
 * Notice: why we don't have to match brackets?
 *      the level of recursion coresponds to the priority of calculation of experssion. So
 *      at every recusrion, the left operand and right operand have the same priority.
 */
int calcHelper(const string& exp, int& index) {
    if (isdigit(exp[index])) { // simplest form of expression
        return exp[index++] - '0';
    }

    if (exp[index] == '(') {
        index++; // skip '('
        int left = calcHelper(exp, index);  // left operand
        char op = exp[index++];             // operator
        int right = calcHelper(exp, index); // right operand
        index++; // skip ')'

        switch (op) {
        case '-':
            return left - right;
            break;
        case '+':
            return left + right;
            break;
        case '*':
            return left * right;
            break;
        case '/':
            if (right != 0) {
                return left / right;
            }
            else {
                error("Error: Zero can not be denominater.");
            }
            break;
        default:
            error("Error: Undefined operator detected.");
        }
    }
    else {
        error("Error: Illegal expression.");
    }
}


/*
 * Function: calculation
 * ------------------------------------
 * The function will calculate the result for the given expression.
 *
 * @param exp: the given expression
 *
 * ex> "7"            => 7
 *     "(2+2)"        => 4
 *     "(1+(2*4))     => 9
 *     "((1+2)*(3+2)) => 15
 */
int calculation(const string& exp) {
    int index = 0;
    return calcHelper(exp, index);
}

/* ****************************** *
 *          UNIT TEST
 * ****************************** */
PROVIDED_TEST("Test for calculation:") {
    EXPECT_EQUAL(calculation("7"), 7);
    EXPECT_EQUAL(calculation("(2+2)"), 4);
    EXPECT_EQUAL(calculation("(1+(2*4))"), 9);
    EXPECT_EQUAL(calculation("((1+2)*(3+2))"), 15);
}

PROVIDED_TEST("Test for error detection of calculation") {
    EXPECT_ERROR(calculation("(0/0)"));
    EXPECT_ERROR(calculation("(1?1)"));
    EXPECT_ERROR(calculation("("));
    EXPECT_ERROR(calculation("(4+"));
}
