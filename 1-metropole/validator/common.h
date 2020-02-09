#ifndef H_COMMON
#define H_COMMON
#include "testlib.h"
#include "bounds.h"
#include <iostream>

using namespace std;


class Checker {
public:
    int maxHyperEdgeSize;
    int totalSize;
    bool allCostOne;

    int V, H;
    vector<int> cost;

    Checker() {
        totalSize = 0;
        maxHyperEdgeSize = 0;
        allCostOne = true;
    };

    void validate() {
        registerValidation();
        V = inf.readInt(MIN_V, MAX_V, "V");
        inf.readSpace();
        H = inf.readInt(MIN_H, MAX_H, "H");
        inf.readEoln();

        for(int i = 0; i < H; i++) {
            int c = inf.readInt(MIN_C, MAX_C, "C");
            cost.push_back(c);
            allCostOne &= c == 1;
            inf.readEoln();

            int n = inf.readInt(2, V);
            totalSize += n;
            inf.readSpace();

            vector<int> vertices = inf.readInts(n, 1, V);
            ensuref(set<int>(vertices.begin(), vertices.end()).size() == vertices.size(), "A station appears twice in one hypergrid");
            inf.readEoln();

            maxHyperEdgeSize = max(maxHyperEdgeSize, n);
        }

        ensuref(totalSize <= MAX_SUM, "Total size of hyperedges is too many");

        inf.readEof();
    }
};

#endif // COMMON_H
