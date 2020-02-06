#include <iostream>
#include <cassert>
#include <vector>
#include <random>

using namespace std;


struct edge {
    int startVertex, endVertex, weight;
    edge(int nStart, int nEnd, int nWeight) : startVertex{nStart},
                                              endVertex{nEnd},
                                              weight{nWeight} {}
};

// Prints:
// V E
// a_1 b_1 c_1
// a_2 b_2 c_2
// .
// .
// .
// a_E b_E c_E
void printData(int V, vector<edge> e) {
    cout << V << " " << e.size() << "\n";
    for(auto x: e) {
        cout << x.startVertex << " " << x.endVertex << " " << x.weight << "\n";
    }
}


mt19937 generator;
bool generatorInitialised;
bool initialiseGenerator(int seed) {
    generatorInitialised = true; 
    generator = mt19937(seed);
}

int randint(int a, int b) {
    assert(generatorInitialised && "randint called before generator was initialised");
    uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

int main(int argc, char* argv[]) {
    if(argc != 6) {
        fprintf(stderr, "Usage: %s <vertices> <K> <minWeight> <maxWeight> <seed>\n", argv[0]);
        exit(1);
    }
    int V = stoi(argv[1]);
    int K = stoi(argv[2]);
    int minW = stoi(argv[3]);
    int maxW = stoi(argv[4]);
    int seed = stoi(argv[5]);
    initialiseGenerator(seed);

    vector<edge> e;
   
    vector<vector<int>> s(K);
    
    for(int i = 2; i <= V-1; i++) {
        s[i%K].push_back(i);
    }

    for(auto x: s[0]) {
        e.emplace_back(1, x, minW);
    }
    for(auto x: s[K-1]) {
        e.emplace_back(V, x, minW);
    }

    for(int i = 1; i < K; i++) {
        for(auto x: s[i]) {
            for(auto y: s[i-1]) {
                e.emplace_back(x, y, minW);
            }
        }
    }

    printData(V, e);
}
