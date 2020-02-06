#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include <algorithm>

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
        fprintf(stderr, "Usage: %s <vertices> <edges> <C> <D> <seed>\n", argv[0]);
        exit(1);
    }
    int V = stoi(argv[1]);
    int E = stoi(argv[2]);
    int C = stoi(argv[3]);
    int D = stoi(argv[4]);
    int seed = stoi(argv[5]);
    initialiseGenerator(seed);

    vector<edge> te;
    for(int i = 1; i <= V; i++) {
        for(int j = i+1; j <= V; j++) {
            int weight = abs(j-i)*C +  randint(-D, D);
            te.emplace_back(i, j, weight);
        }
    }

    vector<edge> e;
    random_shuffle(te.begin(), te.end());
    for(int i = 0; i < E; i++) {
        e.push_back(te[i]);
    }

    printData(V, e);
}
