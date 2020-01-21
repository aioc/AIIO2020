#include <bits/stdc++.h>
using namespace std;

#define FO(i,a,b) for (int i = (a); i < (b); i++)
typedef long long ll;

const int MAXV = 100000;
const int MAXNODES = 200000;
// Node numbering:
//  cities: 1...V
//  stations: MAXV+1 ... MAXV+H

int V, H;
vector<pair<int, ll>> allE[MAXNODES+5];

struct state {
    int p; ll d;
    state(int _p=0, ll _d=0) : p(_p), d(_d) {}
    bool operator < (const state &oth) const {
        return d > oth.d;
    }
};

bool done[MAXNODES+5];

int main() {
    scanf("%d %d", &V, &H);
    FO(h,0,H) {
        int C, S;
        scanf("%d %d", &C, &S);
        vector<int> cities;
        FO(s,0,S) {
            int cC; scanf("%d", &cC);
            cities.push_back(cC);
        }
        for (int c : cities) {
            allE[c].emplace_back(MAXV+h+1, C);
            allE[MAXV+h+1].emplace_back(c, 0);
        }
    }
    priority_queue<state> pq;
    pq.push({1, 0});
    while (!pq.empty()) {
        state cS = pq.top(); pq.pop();
        if (done[cS.p]) continue;
        done[cS.p] = true;
        if (cS.p == V) {
            printf("%lld\n", cS.d);
            return 0;
        }
        for (auto cE : allE[cS.p]) {
            pq.push({cE.first, cS.d + cE.second});
        }
    }
}
