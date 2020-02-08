#include <map>
#include <cassert>
#include <algorithm>
#include <vector>
#include <random>
#include <set>
#include <cmath>

#include "random.h"
#include "bounds.h"

using namespace std;

struct Hyperedge {
    Hyperedge(vector<int> _v, int _w): vertices{_v}, weight{_w} {}
    vector<int> vertices;
    int weight;

    void printdebug() {
        for(auto x: vertices) {
            cout << x << " ";
        }
        cout << "\n";
    }
};

class Graph {
public:
    vector<Hyperedge> e;
    int V;

    Graph(int _V) : V(_V) {}

    // Shortcut for adding a hyperedge with only two vertices
    void addEdge(int a, int b, int w) {
        addEdge({a, b}, w);
    }

    void addEdge(vector<int> vertices, int w) {
        e.emplace_back(vertices, w);
    }

    void addEdge(Hyperedge he) {
        e.push_back(he);
    }

    void addGraph(Graph g) {
        e.insert(e.begin(), g.e.begin(), g.e.end());
    }

    void increment(int x) {
        for(auto& edge: e) {
            for(auto& v: edge.vertices) {
                v += x;
            }
        }
    }

    bool connected(int target) {
        map<int, vector<Hyperedge>> adj;
        for(auto edge: e) {
            for(auto x: edge.vertices) {
                adj[x].push_back(edge);
            }
        }

        set<int> seen;
        queue<int> q;
        q.push(1);
        seen.insert(1);
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            //cerr << "Saw " << cur << "\n";
            for(auto edge: adj[cur]) {
                //cerr << "Considering hyperedge of cost " << edge.weight << "\n";
                for(auto to: edge.vertices) {
                    //cerr << "Let's go to " << to << "\n";
                    if(seen.find(to) == seen.end()) {
                        if(to == target) {
                            //cerr << "Finished!\n";
                            return true;
                        }
                        seen.insert(to);
                        q.push(to);
                    }
                }
            }
        }
        //cerr << "Did not see\n";
        return false;
    }

    void printGraphs(string fileName) {
        printGraph(fileName);
        for(auto& edge: e) {
            edge.weight = 1;
        }
        printGraph("sub3-" + fileName);
    }
    
    void printGraph(string fileName) {
        ofstream out(fileName);
        quickcheck();
        permute();
        shuffle();
        out << V << " " << e.size() << "\n";
        for(auto edge: e) {
            out << edge.weight << "\n";
            out << edge.vertices.size();
            for(auto x: edge.vertices) {
                out << " " << x;
            }
            out << "\n";
        }
    }

    void permute() {
        vector<int> v = makerange(2, V-1);
        vector<int> v2 = makerange(2, V-1);
        random_shuffle(begin(v2), end(v2));
        map<int, int> perm;
        for(auto i = 0u; i < v.size(); i++) {
            perm[v[i]] = v2[i];
        }
        perm[1] = 1;
        perm[V] = V;
        for(auto& edge: e) {
            for(auto& x: edge.vertices) {
                x = perm[x];
            }
        }
    }

    void shuffle() {
        random_shuffle(begin(e), end(e));
        for(auto& edge: e) {
            random_shuffle(begin(edge.vertices), end(edge.vertices));
        }
    }

    void quickcheck() {
        for(auto edge: e) {
            assert(!edge.vertices.empty());
            for(auto x: edge.vertices) {
                //cerr << "Check " << x << "\n";
                assert(1 <= x && x <= V);
            }
        }
    }
};

// Returns a random sample of size k
vector<int> randomSample(const vector<int>& v, unsigned int k) {
    assert(k <= v.size());
    if(k < v.size()/4) {
        set<int> indices;
        while(indices.size() < k) {
            int randomIndex = randint(v.size());
            indices.insert(randomIndex);
        }

        vector<int> ans;
        for(auto idx: indices) {
            ans.push_back(v[idx]);
        }
        return ans;
    } else {
        vector<int> tempV = v;
        random_shuffle(tempV.begin(), tempV.end());
        vector<int> ans;
        ans.insert(ans.end(), tempV.begin(), tempV.begin()+k);
        return ans;
    }
}

// Returns a random sample of size k, where one of the elements is the given.
// v must not include required.
vector<int> randomSampleIncluding(const vector<int>& v, unsigned int k, int required) {
    auto ans = randomSample(v, k-1);
    ans.push_back(required);
    return ans;
}

// Picks a random interval of size "size" in the range [minV, maxV].
// The number of samples in that interval is "sample".
vector<int> randomSamplePickInterval(int minV, int maxV, int size, int sample) {
    assert(sample <= size);
    size = min(size, maxV-minV);
    //cerr << minV << " " << maxV << " " << size << "\n";
    int l = randint(minV, maxV-size);
    int r = l+size-1;
    vector<int> cand = makerange(l, r);
    return randomSample(cand, sample);
}

// V: Total number of vertices
// [minD, maxD]: the range of possible costs, chosen uniformly at random
// minH: the minimum number of hypergraphs to add
// maxJump: Make sure that each hypergraph doesn't go too far.
Graph randomSmart(int V, int minVertices, int maxVertices, int minH, int maxJump) {
    Graph g(V);
    //cerr << "Graph size is " << V << "\n";
    maxJump = min(maxJump, V);
    //cerr << "Max jump is " << maxJump << "\n";

    vector<int> vStart;
    for(int i = 2; i <= maxJump; i++) {
        vStart.push_back(i);
    }
    for(int i = 0; i <= (int)log2(minH); i++) {
        auto v = randomSampleIncluding(vStart, randint(minVertices, maxVertices), 1);
        g.addEdge(v, randint(MIN_C, MAX_C));
    }

    vector<int> vEnd;
    for(int i = V-maxJump+1; i <= V-1; i++) {
        vEnd.push_back(i);
    }
    for(int i = 0; i <= (int)log2(minH); i++) {
        auto v = randomSampleIncluding(vEnd, randint(minVertices, maxVertices), V);
        g.addEdge(v, randint(MIN_C, MAX_C));
    }

    //cerr << g.e.size() << " < " << minH  << "\n";
    while((int)g.e.size() < minH) {
        //if(g.e.size() % 1000 == 0) { //cerr << "Got to " << g.e.size() << "\n";}
        auto v = randomSamplePickInterval(2, V-1, maxJump, randint(minVertices, maxVertices));
        g.addEdge(v, randint(MIN_C, MAX_C));
    }

    int stepSize = 10;
    while(!g.connected(V)) {
        //cerr << "Step size " << stepSize << "\n";
        for(int i = 0; i < stepSize; i++) {
            auto v = randomSamplePickInterval(2, V-1, maxJump, randint(minVertices, maxVertices));
            g.addEdge(v, randint(MIN_C, MAX_C));
        }
        stepSize += 10;
    }

    return g;
}

Graph randomSmartCombine(int verticesPerGraph, int verticesPerEdge, int edgesPerGraph, int maxJump, int numGraphs) {
    Graph g((verticesPerGraph-1)*numGraphs + 1);
    for(int i = 0; i < numGraphs; i++) {
        //cerr << "Looking at graph " << i << "\n";
        Graph curG = randomSmart(verticesPerGraph, verticesPerEdge, verticesPerEdge, edgesPerGraph, maxJump);
        curG.quickcheck();
        curG.increment(max(0, i*(verticesPerGraph-1)));
        g.addGraph(curG);
    }

    assert(g.connected(g.V));
    return g;
}

Graph intervalGraph(int V, int D) {
    Graph g(V);
    for(int i = 1; i+D-1 <= V; i++) {
        auto v = makerange(i, i+D-1);
        g.addEdge(v, randint(MIN_C, MAX_C));
    }
    return g;
}

Graph intervalGraphInc(int V, int D) {
    Graph g(V);
    vector<int> vs;
    for(int i = 1; i+D-1 <= V; i++) {
        vs.push_back(randint(MIN_C, MAX_C));
    }
    sort(begin(vs), end(vs));

    for(int i = 1; i+D-1 <= V; i++) {
        auto v = makerange(i, i+D-1);
        g.addEdge(v, vs[i-1]);
    }
    return g;
}

int pointToInt(int r, int c, int R, int C) {
    assert(r <= R);
    assert(c <= C);
    return (r-1)*C + c;
}

// Grid order:
// 1 2 3 ... C
// C+1 C+2 ... 2C
// ...
// C*(R-1)+1 C*(R-1)+2 ... RC
Graph grid(int R, int C, int dr, int dc) {
    Graph g(R*C);
    for(int rtl = 1; rtl + dr - 1 <= R; rtl++) {
        for(int ctl = 1; ctl + dc - 1 <= C; ctl++) {
            vector<int> v;
            for(int _dr = 0; _dr < dr; _dr++) {
                for(int _dc = 0; _dc < dc; _dc++) {
                    v.push_back(pointToInt(rtl + _dr, ctl + _dc, R, C));
                }
            }
            g.addEdge(v, randint(MIN_C, MAX_C));
        }
    }
    return g;
}

Graph gridOverlay(int R, int C, int D) {
    Graph g(R*C);
    g.addGraph(grid(R, C, 1, D));
    g.addGraph(grid(R, C, D, 1));
    return g;
}

Graph intervalGraphPlusLargeGrid(int V, int D, int X) {
    Graph g = intervalGraph(V, D);
    for(auto& edge: g.e) {
        edge.weight = randint(1, 10);
    }
    for(int i = 0; i < 40; i++) {
        g.addEdge(randomSample(makerange(1, V), X), randint(MIN_C, MAX_C));
    }
    return g;
}
