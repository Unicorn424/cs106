/**
 * File: perfect.h
 *
 * This is just here to communicate the prototype 
 * information for the functions in perfect.cpp that 
 * will be called from main.cpp
 */
#pragma once
#include <vector>

long divisorSum(long n);
bool isPerfect(long n);
void findPerfects(long stop);

long smarterSum(long n);
bool isPerfectSmarter(long n);
void findPerfectsSmarter(long stop);

long findNthPerfectEuclid(long n);
std::vector<int> getPrimeTable(int max_num);
long getNthPrime(long n);
