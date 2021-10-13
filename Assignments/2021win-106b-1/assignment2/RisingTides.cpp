#include "RisingTides.h"
#include "GUI/SimpleTest.h"
#include "queue.h"
using namespace std;

/*
 * Function: floodedRegionIn
 * ------------------------------------
 * The function will pinpoint all water areas on the given terrain with BFS.
 *
 * @param terrain: a grid describing a terrain
 * @param sources: indicate where water sources are
 * @param height: indicate the maximum of water height
 *
 * The function is implemented in breath search first (BFS) algorithm.
 * 1. put all water sources into water queue.
 * 2. search all possible areas those could be flooded from waterpoints in the queue.
 * 3. update queue.
 */
Grid<bool> floodedRegionsInWithBug(const Grid<double>& terrain,
                            const Vector<GridLocation>& sources,
                            double height) {
    Queue<GridLocation> waterQueue;
    Grid<bool> waterTerrain(terrain.numRows(), terrain.numCols());

    // enqueue all water sources
    for (GridLocation source : sources) {
        waterTerrain[source.row][source.col] = true;
        waterQueue.enqueue(source);
    }

    while (!waterQueue.isEmpty()) {
        GridLocation source = waterQueue.dequeue();

        // if cells in cardinal directions will be flooded
        int row = source.row; int col = source.col;
        if ((terrain.inBounds(row-1, col) && (terrain[row-1][col] <= height))) {
            waterTerrain[row-1][col] = true;
            waterQueue.enqueue(GridLocation(row-1, col));
        }
        if ((terrain.inBounds(row+1, col) && (terrain[row+1][col] <= height))) {
            waterTerrain[row+1][col] = true;
            waterQueue.enqueue(GridLocation(row+1, col));
        }
        if ((terrain.inBounds(row, col-1) && (terrain[row][col-1] <= height))) {
            waterTerrain[row][col-1] = true;
            waterQueue.enqueue(GridLocation(row, col-1));
        }
        if ((terrain.inBounds(row, col+1) && (terrain[row][col+1] <= height))) {
            waterTerrain[row][col+1] = true;
            waterQueue.enqueue(GridLocation(row, col+1));
        }
    }

    return waterTerrain;
}

/* If the cell is a water cell, we should not enqueue the cell, which
 * will cause dead lock.
 * ex> 0 0 0
 *     0 0 0
 *     0 0 0    with height 1
 * The queue will always be non-empty.
 * Solution: if a cell is a water cell, don't put it in the queue.
 */
Grid<bool> floodedRegionsIn(const Grid<double>& terrain,
                            const Vector<GridLocation>& sources,
                            double height) {
    Queue<GridLocation> waterQueue;
    Grid<bool> waterTerrain(terrain.numRows(), terrain.numCols());

    // enqueue all water sources
    for (GridLocation source : sources) {
        waterTerrain[source.row][source.col] = true;
        waterQueue.enqueue(source);
    }

    while (!waterQueue.isEmpty()) {
        GridLocation source = waterQueue.dequeue();

        // if cells in cardinal directions will be flooded
        int row = source.row; int col = source.col;
        if ((terrain.inBounds(row-1, col)) &&
            (!waterTerrain[row-1][col]) &&
            (terrain[row-1][col] <= height)) {
            waterTerrain[row-1][col] = true;
            waterQueue.enqueue(GridLocation(row-1, col));
        }
        if ((terrain.inBounds(row+1, col)) &&
            (!waterTerrain[row+1][col]) &&
            (terrain[row+1][col] <= height)) {
            waterTerrain[row+1][col] = true;
            waterQueue.enqueue(GridLocation(row+1, col));
        }
        if ((terrain.inBounds(row, col-1)) &&
            (!waterTerrain[row][col-1]) &&
            (terrain[row][col-1] <= height)) {
            waterTerrain[row][col-1] = true;
            waterQueue.enqueue(GridLocation(row, col-1));
        }
        if ((terrain.inBounds(row, col+1)) &&
            (!waterTerrain[row][col+1]) &&
            (terrain[row][col+1] <= height)) {
            waterTerrain[row][col+1] = true;
            waterQueue.enqueue(GridLocation(row, col+1));
        }
    }

    return waterTerrain;
}



/***** Test Cases Below This Point *****/
PROVIDED_TEST("Nothing gets wet if there are no water sources.") {
    Grid<double> world = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        // empty
    };

    /* There are no water sources, so nothing should be underwater. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false, false, false },
        { false, false, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Everything gets wet if all locations are below the water level.") {
    Grid<double> world = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Everything should flood; there are no barriers to stop the water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true,  true },
        {  true,  true,  true },
        {  true,  true,  true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't cross a vertical levee.") {
    Grid<double> world = {
        { 0, 2, 0 },
        { 0, 2, 0 },
        { 0, 2, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Only locations to the left of the barrier should be under water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true, false, false },
        {  true, false, false },
        {  true, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't cross a diagonal levee.") {
    Grid<double> world = {
        { 0, 0, 2 },
        { 0, 2, 0 },
        { 2, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Water only flows in the four cardinal directions, so it can't
     * pass through the barrier. Only the top should be flooded.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true, false },
        {  true, false, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't flow diagonally.") {
    Grid<double> world = {
        { 0, 2, 0 },
        { 2, 0, 2 },
        { 0, 2, 0 }
    };

    Vector<GridLocation> sources = {
        { 1, 1 }
    };

    /* Water should be trapped in the center, since it can't move
     * diagonally.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false, false, false },
        { false,  true, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can flow in all cardinal directions.") {
    Grid<double> world = {
        { 2, 0, 2 },
        { 0, 0, 0 },
        { 2, 0, 2 }
    };

    Vector<GridLocation> sources = {
        { 1, 1 }
    };

    /* The water in this case should flow up, down, left, and right. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false,  true, false },
        {  true,  true,  true },
        { false,  true, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can flow from multiple sources.") {
    Grid<double> world = {
        { 0, 0, 2 },
        { 0, 2, 0 },
        { 2, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 },
        { 2, 2 }
    };

    /* Everything except the levee should be under water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true, false },
        {  true, false,  true },
        { false,  true,  true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Handles asymmetric worlds and non-square grids") {
    Grid<double> world = {
        { 3, 1, 4, 1 },
        { 5, 9, 2, 6 },
        { 5, 3, 5, 8 }
    };

    /* Initial test - water shouldn't leak out from the 2 if the height is 3.5. */
    Vector<GridLocation> sources = {
        { 1, 2 }
    };

    Grid<bool> expected = {
        { false, false, false, false },
        { false, false,  true, false },
        { false, false, false, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 3.5), expected);

    /* Now, increase the water height to 4.5. */
    expected = {
        {  true,  true,  true,  true },
        { false, false,  true, false },
        { false, false, false, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 4.5), expected);

    /* Now, increase the water height to 5.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true, false,  true, false },
        {  true,  true,  true, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 5.5), expected);

    /* Now, increase the water height to 6.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true, false,  true,  true },
        {  true,  true,  true, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 6.5), expected);

    /* Now, increase the water height to 9.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true,  true,  true,  true },
        {  true,  true,  true,  true },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 9.5), expected);
}

PROVIDED_TEST("Stress test: Handles a large, empty world quickly.") {
    Grid<double> world(100, 100); // Large world, everything defaults to 0 height.
    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* This may take a long time to complete if the solution is inefficient. Look
     * for things like
     *
     * 1. passing around large objects by *value* rather than by *reference*,
     * 2. revisiting the same squares multiple times (e.g. flooding the same
     *    cell many times due to not checking if something is flooded),
     *
     * etc.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    EXPECT_EQUAL(water.numRows(), world.numRows());
    EXPECT_EQUAL(water.numCols(), world.numCols());

    /* Everything should be flooded. */
    for (int row = 0; row < world.numRows(); row++) {
        for (int col = 0; col < world.numCols(); col++) {
            EXPECT_EQUAL(water[row][col], true);
        }
    }
}
