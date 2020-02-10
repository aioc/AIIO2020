#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int MAX_V = 1e5+5;
const long long int INF = 1e12;

struct edge {
    vector<int> tos;
    int idx;
};

struct state {
    int at, dist;
    state(int _at, long long int _dist) : at(_at), dist(_dist) {}

    bool operator<(const state& oth) const {
        return dist > oth.dist;
    }
};

vector<edge> adj[MAX_V];

int V, E;
int main() {
    cin >> V >> E;
    for(int i = 0; i < E; i++) {
        long long int cost;
        int p;
        cin >> cost >> p;
        vector<int> v;
        for(int j = 0; j < p; j++) {
            int tmp;
            cin >> tmp;
            v.push_back(tmp);
        }
        edge e;
        e.tos = v;
        e.idx = i+1;
        for(auto x: v) {
            adj[x].push_back(e);
        }
    }

    vector<bool> seenV(V+1, false);
    vector<bool> seenH(E+1, false);
    vector<long long int> dist(V+1, INF);

    queue<int> q;
    q.emplace(1);
    dist[1] = 0;
    seenV[1] = true;

    while(!q.empty()) {
        int cur = q.front(); q.pop();
        for(auto e: adj[cur]) {
            if(!seenH[e.idx]) {
                seenH[e.idx] = true;
                for(auto to: e.tos) {
                    if(!seenV[to]) {
                        seenV[to] = true;
                        q.push(to);
                        dist[to] = dist[cur]+1;
                    }
                }
            }
        }
    }
    cout << dist[V] << "\n";
}
