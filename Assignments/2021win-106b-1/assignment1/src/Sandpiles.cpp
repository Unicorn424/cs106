/* File: Sandpile.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 */
#include "Sandpiles.h"
#include "GUI/SimpleTest.h"
#include "queue.h"
using namespace std;

class Seed {
public:
    Seed(int row, int col) {
        this->row = row;
        this->col = col;
    }

    int row;
    int col;
};

/*
 * Function: dropSandOnHelper
 * ------------------------------------
 * The function is going to simulate droping a seed on the cell of a grid
 * and changes recursively.
 *
 * @param world: a grid with the size of row and col
 * @param toppleSeed: seeds to topple
 *
 * Base case:
 *    When there is no seed to topple in the queue.
 * Recursion body:
 * 1. Get the first seed to topple in the queue.
 * 2. Topple it and update cells around it.
 * 3. If there are new seeds to topple, put them into the queue.
 * 4. call helper function to topple seeds in the queue.
 */
void dropSandOnHelper(Grid<int>& world,
                      Queue<Seed>& toppleSeeds) {
    if (!toppleSeeds.isEmpty()) {
        Seed cur = toppleSeeds.dequeue();
        int row = cur.row; int col = cur.col;

        // topple and update adjacent cells
        world[row][col] = 0;
        if (world.inBounds(row+1, col)) world[row+1][col]++; // down
        if (world.inBounds(row-1, col)) world[row-1][col]++; // up
        if (world.inBounds(row, col-1)) world[row][col-1]++; // left
        if (world.inBounds(row, col+1)) world[row][col+1]++; // right

        // update queue
        if (world[row+1][col] >= 4) toppleSeeds.enqueue(Seed(row+1, col));
        if (world[row-1][col] >= 4) toppleSeeds.enqueue(Seed(row-1, col));
        if (world[row][col+1] >= 4) toppleSeeds.enqueue(Seed(row, col+1));
        if (world[row][col-1] >= 4) toppleSeeds.enqueue(Seed(row, col-1));

        dropSandOnHelper(world, toppleSeeds);
    }
}

// @param row & col: drop a seed on world[row][col]
void dropSandOn(Grid<int>& world, int row, int col) {
    Queue<Seed> toppleSeeds;
    // drop one seed on the check
    world[row][col]++;

    // update queue toppleSeeds
    for (int i = 0; i < world.numRows(); i++) {
        for (int j = 0; j < world.numCols(); j++) {
            if (world[i][j] >= 4) {
                toppleSeeds.enqueue(Seed(i, j));
            }
        }
    }

    dropSandOnHelper(world, toppleSeeds);
}

/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Dropping into an empty cell only changes that cell.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 3, 3, 3 },
        { 3, 0, 3 },
        { 3, 3, 3 }
    };
    Grid<int> after = {
        { 3, 3, 3 },
        { 3, 1, 3 },
        { 3, 3, 3 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Non-chaining topples work.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0 },
        { 1, 3, 1 },
        { 0, 2, 0 }
    };
    Grid<int> after = {
        { 0, 1, 0 },
        { 2, 0, 2 },
        { 0, 3, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

PROVIDED_TEST("Two topples chain.") {
    /* Create a simple source grid. */
    Grid<int> before = {
        { 0, 0, 0, 0 },
        { 0, 3, 3, 0 },
        { 0, 0, 0, 0 }
    };
    Grid<int> after = {
        { 0, 1, 1, 0 },
        { 1, 1, 0, 1 },
        { 0, 1, 1, 0 }
    };

    dropSandOn(before, 1, 1);
    EXPECT_EQUAL(before, after); // The above call changes 'before.'
}

/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */










