/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include <cmath>        // for sqrt
#include <vector>
#include "testing/SimpleTest.h"
using namespace std;

/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* This function is an improved method of calculating the sum of all proper
 * divisors of 'n'. It's more efficient to check from 2 to
 */
long smarterSum(long n) {
    // divisor 1 for all 'n' except 1
    long total = 1;

    // special case:
    if ((n == 1) || (n == 0)) {
        return 0;
    }

    for (long i = 2; i <= floor(sqrt(n)); i++) {
        if (n % i == 0) {
            total = total + i + n / i;
        }
    }

    return total;
}

/* The function will check if the number is a perfect number.
 */
bool isPerfectSmarter(long n) {
    return (n != 0) && (n == smarterSum(n));
}

/* The function does the same work with findPerfects
 */
void findPerfectsSmarter(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}


/* The function will print prime table within given boundary
 */
vector<int> getPrimeTable(int max_num) {
    vector<bool> primeTable(max_num, true);
    vector<int> primeList;

    // 0 and 1 are not prime numbers
    primeTable[0] = primeTable[1] = false;

    for (int i = 2; i < max_num; i++) {
        if (primeTable[i]) {
            int index = 2 * i;
            while (index < max_num) {
                primeTable[index] = false;
                index += i;
            }
        }
    }

    for (int i = 0; i < max_num; i++) {
        if (primeTable[i]) {
            primeList.push_back(i);
        }
    }

    return primeList;
}

/* The function will return Nth prime
 */
long getNthPrime(long n) {
    vector<int> primeList = getPrimeTable(1000);

    return primeList[n-1];
}


/* The function will return Nth perfect number
 * The power of math: all perfect number follow the pattern of 2^(p-1) * (2^p - 1)
 * for p = 2:   21(22 − 1) = 2 × 3 = 6
 * for p = 3:   22(23 − 1) = 4 × 7 = 28
 * for p = 5:   24(25 − 1) = 16 × 31 = 496
 * for p = 7:   26(27 − 1) = 64 × 127 = 8128.
 */
long findNthPerfectEuclid(long n) {
    long nPrime = getNthPrime(n);

    return pow(2, nPrime-1) * (pow(2, nPrime) - 1);
}


/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Oddballs, zero, one, negative") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
    EXPECT(!isPerfect(-6));
}

PROVIDED_TEST("33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time multiple trials of findPerfects on doubling input sizes") {
    cout << endl;
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
    TIME_OPERATION(80000, findPerfects(80000));
//    TIME_OPERATION(160000, findPerfects(160000));
//    TIME_OPERATION(320000, findPerfects(320000));
//    TIME_OPERATION(640000, findPerfects(640000));
}

// TODO: add your student test cases here

STUDENT_TEST("Check if get Nth prime number works") {
    EXPECT_EQUAL(getNthPrime(1), 2);
    EXPECT_EQUAL(getNthPrime(2), 3);
    EXPECT_EQUAL(getNthPrime(5), 11);
}

STUDENT_TEST("Check if SmarterSum works") {
    EXPECT_EQUAL(smarterSum(0), 0);
    EXPECT_EQUAL(smarterSum(6), 6);
    EXPECT_EQUAL(smarterSum(10), 8);
}

STUDENT_TEST("Time multiple trials of findPerfectsSmarter on doubling input size") {
    cout << endl;
    TIME_OPERATION(10000, findPerfectsSmarter(10000));
    TIME_OPERATION(20000, findPerfectsSmarter(20000));
    TIME_OPERATION(40000, findPerfectsSmarter(40000));
    TIME_OPERATION(80000, findPerfectsSmarter(80000));
}
