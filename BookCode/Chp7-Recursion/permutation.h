#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <string>
#include "vector.h"
using namespace std;

/*
 * Function: permutation
 * Usage: Vector<string> result = permutation(str)
 * ------------------------------------
 * The function will return a vector with all permutation strings of given string.
 */
Vector<string> permutaion(string str);
Vector<string> permutationWithoutRep(string str);

#endif // PERMUTATION_H
