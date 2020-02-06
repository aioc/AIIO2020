#include <iostream>

#include "bounds.h"
#include "graph.h"

const int INF_JUMP = MAX_V;

const int SQRT_V = sqrt(MAX_V);

string strip(string filename) {
    // Taken from: https://stackoverflow.com/questions/8520560/get-a-file-name-from-a-path
    const size_t last_slash_idx = filename.find_last_of("\\/");
    if (std::string::npos != last_slash_idx) {
        filename.erase(0, last_slash_idx + 1);
    }
    return filename;
}

int main(int argc, char* argv[]) {
    assert(argc == 2);
    initialiseGenerator(918247);
    ifstream in(argv[1]);
    ofstream out(strip(argv[1]));

    int V, E;
    in >> V >> E;
    out << V << " " << E << "\n";
    for(int i = 1; i <= E; i++) {
        int a, b, c;
        in >> a >> b >> c;
        out << c << "\n";
        out << "2 " << a << " " << b << "\n";
    }
}

