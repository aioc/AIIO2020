#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <tuple>
#include <cassert>
#include <queue>
#include <random>
#include <algorithm>

#ifndef RANDOM_H
#define RANDOM_H

using namespace std;

//
// Random functions
//
mt19937 generator;
bool generatorInitialised;
void initialiseGenerator(int seed) {
    generatorInitialised = true; 
    generator = mt19937(seed);
}

// Random int in [a, b]
int randint(int a, int b) {
    assert(a <= b);
    assert(generatorInitialised && "randint called before generator was initialised");
    uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

// Random int in [0, x)
int randint(int x) {
    return randint(0, x-1);
}

// Random double in [a, b]
double randdouble(double a, double b) {
    assert(a < b);
    assert(generatorInitialised && "randdouble called before generator was initialised");
    uniform_real_distribution<double> distribution(a, b);
    return distribution(generator);
}

map<pair<int, int>, vector<int>> mv;
// Convenience method for returning a vector containing values in a given range
vector<int> makerange(int a, int b) {
    if(mv.find({a, b}) == mv.end()) {
        vector<int> v;
        for(int i = a; i <= b; i++) {
            v.push_back(i);
        }
        mv[{a, b}] = v;
    }
    return mv[{a, b}];
}

#endif // RANDOM_H
