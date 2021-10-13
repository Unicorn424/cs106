/*
 * File: main.cpp
 * --------------
 * Random Library
 */

#include <iostream>
#include "console.h"
#include "random.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * This sample main brings up testing menu.
 */
int main() {
    cout << "On this machine, RAND_MAX is " << RAND_MAX << endl;
    for (int i = 0; i < 10; i++) {
        cout << RandomInteger(1, 6) << endl;
    }

    return 0;
}

PROVIDED_TEST("Sample use of SimpleTest")
{
    EXPECT_EQUAL(1 + 1, 2);
}
