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
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <groups> <seed>\n", argv[0]);
        exit(1);
    }
    int G = stoi(argv[1]);
    int seed = stoi(argv[2]);
    initialiseGenerator(seed);

    int V = 3*G+1;

    vector<edge> e;
    for(int i = 0; i < G; i++) {
        int l = 3*i+1;
        int u = 3*i+2;
        int d = 3*i+3;
        int r = 3*i+4;
        e.emplace_back(l, u, randint(1e5/2 + 1, 1e5));
        e.emplace_back(l, d, randint(1e5/2 + 1, 1e5));
        e.emplace_back(u, r, randint(0, 1e5/2));
        e.emplace_back(d, r, randint(0, 1e5/2));
    }

    printData(V, e);
}
