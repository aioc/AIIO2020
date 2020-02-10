#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int MAX_V = 1e5+5;
const long long int INF = 1e12;

struct edge {
    int to;
    long long int cost;

    edge(int _to, long long  int _cost) : to(_to), cost(_cost) {}
};

struct state {
    int at, dist;
    state(int _at, long long int _dist) : at(_at), dist(_dist) {}

    bool operator<(const state& oth) const {
        return dist > oth.dist;
    }
};

vector<edge> adj[MAX_V];

void addEdge(int x, int y, long long int c) {
    adj[x].emplace_back(y, c);
    adj[y].emplace_back(x, c);
}

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
        for(auto x: v) {
            for(auto y: v) {
                addEdge(x, y, cost);
            }
        }
    }

    vector<bool> seen(V+1, false);
    vector<long long int> dist(V+1, INF);

    priority_queue<state> pq;
    pq.emplace(1, 0);
    dist[1] = 0;

    while(!pq.empty()) {
        state cur = pq.top(); pq.pop();
        if(!seen[cur.at]) {
            seen[cur.at] = true;
            for(auto e: adj[cur.at]) {
                long long int newCost = dist[cur.at] + e.cost;
                if(dist[e.to] > newCost) {
                    dist[e.to] = newCost;
                    pq.emplace(e.to, newCost);
                }
            }
        }
    }
    cout << dist[V] << "\n";
}
