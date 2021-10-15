#include <iostream>
#include "console.h"
using namespace std;

int main() {

    int* arr = new int[3];

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    delete[] arr;

    arr = new int[4];

    delete[] arr;

    return 0;

}
