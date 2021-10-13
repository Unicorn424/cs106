#ifndef RANDOM_H
#define RANDOM_H

/*
 * Function: RandomInteger
 * Usage: int n = RandomInteger(low, high);
 */
int RandomInteger(int low, int high);

/*
 * Function: RandomReal
 * Usage: double d = RandomReal(low, high);
 */
double RandomReal(double low, double high);

/*
 * Function: RandomChance
 * Usage: if (RandomChance(p)) ...
 */
bool RandomChance(double p);

/*
 * Function: SetRandomSeed
 * Usage: SetRandomSeed(seed)
 * The reason why 'S' is capital is that setRandomSeed is a builtin function somewhere.
 */
void SetRandomSeed(int seed);

/*
 * Function: initRandomSeed
 * Usage: initRandomSeed();
 */
void initRandomSeed();

#endif // RANDOM_H
