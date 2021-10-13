/*
 * File: main.cpp
 * --------------
 * This is a demo project for string library.
 */

#include <iostream>
#include "console.h"
#include "testing/SimpleTest.h"
#include "standardlibrary.h"
using namespace std;

int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }

//    unknown();

    return 0;
}
