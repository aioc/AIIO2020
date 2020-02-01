#ifndef H_COMMON
#define H_COMMON
#include "testlib.h"
#include "bounds.h"
#include <iostream>

using namespace std;

void validate(int MAX_R, int MAX_C, int MIN_P, int MAX_P) {
    registerValidation();
    const int MIN_R = MAX_R == 2 ? 2 : 1;
    int R = inf.readInt(MIN_R, MAX_R, "R");
    inf.readSpace();
    int C = inf.readInt(1, MAX_C, "C");
    inf.readEoln();

    for(int r = 1; r <= R; r++) {
        inf.readInts(C, MIN_P, MAX_P);
        inf.readEoln();
    }
    inf.readEof();
}

#endif // COMMON_H
