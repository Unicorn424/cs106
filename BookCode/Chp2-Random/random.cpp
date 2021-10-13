#include "random.h"
#include <cmath>   // for floor(float)
#include <cstdlib> // for rand() and RAND_MAX
#include <ctime>   // for time() and NULL

/*
 * ex: RandomInteger(1, 6)
 * - Initial call to rand(): 84825604
 * - Normalization: 0.4
 * - Scaling: 2.4 (0.4 * ((6 - 1) + 1))
 * - Translation and conversion: int(floor(1 + 2.4)) = 3
 * 1     2     3     4     5     6    (7)
 * |-----|-----|-----|-----|-----|-----o
 */
int RandomInteger(int low, int high) {
    initRandomSeed();
    // Normalization: the reason for typecast here is RAND_MAX is the max number for int
    double d = rand() / (double(RAND_MAX) + 1);
    // typecast: "high - low" may overflow when comes to int
    double scale = d * (double(high) - low + 1);

    return int(floor(low + scale));
}

double RandomReal(double low, double high) {
    initRandomSeed();
    double d = rand() / (double(RAND_MAX) + 1);
    double scale = d * (high - low);

    return low + scale;
}

bool RandomChance(double p) {
    return RandomReal(0, 1) < p;
}

// for debug
void SetRandomSeed(int seed) {
    initRandomSeed();
    srand(seed); // override random seed
}

void initRandomSeed() {
    static bool initialized = false;
    if (!initialized) {
        srand(int(time(NULL)));
        initialized = true;
    }
}
