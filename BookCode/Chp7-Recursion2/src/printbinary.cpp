#include "printbinary.h"
#include <iostream>
using namespace std;

/*
 * Function: printBinary
 * ------------------------------------
 * The function will print the binary of the given number
 *
 * ex> printBinary(13)    =>    1101
 *
 * @param num: the given number to be tranlated into binary form
 *
 * 13 % 2 = 1               =>   13 = 1101
 * 13 / 2 = 6   6 % 2 = 0   =>    6 = 110
 *  6 / 2 = 3   3 % 2 = 1   =>    3 = 11
 *  1 / 2 = 1   1 % 2 = 1   =>    1 = 1
 *
 * The basic idea is I can print the last digit, and then print the rest.
 * ex> when num = 13, I will know that the last digit is 13 mod 2, and the
 * rest digits before it must be the binary of 13 div 2.
 *      13 = 1101 = 110 + 1
 *                   ^    ^
 *                  rest last
 *
 * The intuition is that, given 6 = 110, I will build 12 by shift left '110'
 * by 1 bit and add 0 (12 % 2) to the last. So 12 = 1100.
 *
 * Base case:
 *      the binary of 1 and 0 is itself.
 * Recursion:
 *      - The last binary digit of 'num' is num % 2.
 *      - Print binary number of (num / 2).
 *      - print the last digit.
 */
void printBinary(int num) {
    if (num <= 1) {
        cout << num;
        return;
    }

    int lastdigit = num % 2;
    int rest = num / 2;
    printBinary(rest);
    cout << lastdigit;
}

int main_away() {
    printBinary(12);

    return 0;
}
