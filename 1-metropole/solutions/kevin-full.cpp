#include<bits/stdc++.h>
#include <iostream>

using namespace std;

int N, G;

const int MAX_G = 1e6+5;
const int MAX_N = 1e6+5;
const int INF = 1e9;

vector<int> grid[MAX_G];
vector<int> adj[MAX_N];
int cost[MAX_G];

int dist[MAX_N];
bool seen[MAX_N];

bool gseen[MAX_N];

struct state {
    int at, d;
    state(int _at, int _d) : at{_at}, d{_d} {}
    bool operator<(const state& oth) const {
        return d > oth.d;
    }
};

int main() {
    cin >> N >> G;
    for(int i = 1; i <= G; i++) {
       int x;

       cin >> x;
       cost[i] = x;

       cin >> x;
       for(int j = 1; j <= x; j++) {
           int y;
           cin >> y;
           grid[i].push_back(y);
           adj[y].push_back(i);
       }
    }

    for(int i = 2; i <= N; i++) {
        dist[i] = INF;
    }

    priority_queue<state> pq;
    pq.emplace(1, 0);
    while(pq.size()) {
        state cur = pq.top(); pq.pop();
        //cerr << "Expanding " << cur.at << "\n";
        if(cur.at == N) {
            cout << cur.d << "\n";
            return 0;
        }
        if(!seen[cur.at]) {
            seen[cur.at] = true;
            for(auto g: adj[cur.at]) {
                if(!gseen[g]) {
                    //cerr << "considering grid " << g << "\n";
                    gseen[g] = true;
                    for(auto to: grid[g]) {
                        if(dist[to] > dist[cur.at] + cost[g]) {
                            dist[to] = dist[cur.at] + cost[g];
                            pq.emplace(to, dist[to]);
                        }
                    }
                }
            }
        }
    }
}
