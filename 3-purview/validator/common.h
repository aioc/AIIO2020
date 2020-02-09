#ifndef H_COMMON
#define H_COMMON
#include "testlib.h"
#include "bounds.h"
#include <iostream>

using namespace std;


class Checker {
public:
    bool DisZero;
    bool onlyRightDemolished;
    bool demolishedInOrder;
    bool smallN;

    string S;
    vector<int> demolitions;
    vector<int> quotas;
    int N, D;

    Checker() {};

    void checkDemolitions() {
        set<int> seen(demolitions.begin(), demolitions.end());
        ensuref(seen.size() == demolitions.size(), "Statue demolished more than once");

        DisZero = demolitions.empty();

        onlyRightDemolished = true;
        for(auto x: demolitions) {
            onlyRightDemolished &= S[x-1] == 'R';
        }

        demolishedInOrder = true;
        for(int i = 0; i < (int)demolitions.size(); i++) {
            demolishedInOrder &= demolitions[i] == i+1;
        }
        demolishedInOrder &= (int)demolitions.size() == N-1;
    }

    void validate() {
        registerValidation();
        N = inf.readInt(MIN_N, MAX_N, "N");
        smallN = N <= SMALL_N;
        inf.readSpace();
        D = inf.readInt(0, N-1, "D");
        inf.readEoln();

        S = inf.readString("[LR]+", "S"); // readString automatically reads an EOLN as well
        ensuref((int)S.size() == N, "Must have one character per statue");

        quotas = inf.readInts(N,  MIN_F, MAX_F);
        inf.readEoln();

        demolitions = inf.readInts(D, 1, N);
        inf.readEoln();

        checkDemolitions();

        inf.readEof();
    }
};

#endif // COMMON_H
