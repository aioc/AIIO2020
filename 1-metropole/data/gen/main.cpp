#include <iostream>

#include "bounds.h"
#include "graph.h"

const int INF_JUMP = MAX_V;

const int SQRT_V = sqrt(MAX_V);

int main() {
    initialiseGenerator(918247);

    assert(pointToInt(1, 1, 1, 10) == 1);
    assert(pointToInt(2, 1, 10, 10) == 11);
    assert(pointToInt(2, 5, 15, 10) == 15);
    assert(pointToInt(10, 10, 10, 10) == 100);

    // Subtask 2 (S_i <= 4)
    intervalGraph(3*MAX_V/4, 4).printGraphs("G2-1.in");
    intervalGraphInc(3*MAX_V/4, 4).printGraphs("G2-2.in");

    randomSmart(MAX_V, 4, 4, MAX_H*3/4, INF_JUMP).printGraphs("R2-1.in");
    randomSmart(MAX_V, 4, 4, MAX_H*3/4, INF_JUMP).printGraphs("R2-2.in");
    randomSmart(MAX_V, 4, 4, MAX_H*3/4, 30).printGraphs("R2-3.in");

    randomSmartCombine(10, 4, 10000/4, INF_JUMP, 20).printGraphs("J1.in");

    grid(SQRT_V, SQRT_V, 2, 2).printGraphs("S2-1.in");
    gridOverlay(SQRT_V/2, SQRT_V/2, 4).printGraphs("S2-overlay.in");
    
    // Subtask 4 (C_i = 1)
    intervalGraph(MAX_V, MAX_V-2).printGraphs("G4-1.in");
    intervalGraph(3*SQRT_V, SQRT_V).printGraphs("G4-2.in");
    intervalGraphInc(MAX_V/10, 10).printGraphs("G4-3.in");

    intervalGraphPlusLargeGrid(MAX_V/10, 10, MAX_V/20).printGraphs("B1.in");

    randomSmart(MAX_V/2, 30, 30, MAX_H/30, MAX_V/2).printGraphs("R4-1.in");
    randomSmart(MAX_V, 10000, 10000, 3*MAX_H/10000, MAX_V).printGraphs("R4-2.in");
    randomSmart(MAX_V, 2, 10000, 50, MAX_V).printGraphs("R4-3.in");
    randomSmart(MAX_V, 30, 30, MAX_H/30, 100).printGraphs("R4-4.in");
}
