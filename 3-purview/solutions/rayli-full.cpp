#include <bits/stdc++.h>
using namespace std;

#define FO(i,a,b) for (int i = (a); i < (b); i++)
typedef long long ll;

const int INF = (1e9 + 5);
const int MAXN = 100000;

ll lazyadd[3*MAXN+5];
ll rtmax[3*MAXN+5];

void propagate(int cN) {
    lazyadd[cN*2] += lazyadd[cN];
    rtmax[cN*2] += lazyadd[cN];
    lazyadd[cN*2+1] += lazyadd[cN];
    rtmax[cN*2+1] += lazyadd[cN];
    lazyadd[cN] = 0;
}

// [)
void update(int qL, int qR, int qV, int cL=1, int cR=MAXN+1, int cN=1) {
    if (qL <= cL && cR <= qR) {
        lazyadd[cN] += qV;
        rtmax[cN] += qV;
        return;
    }
    if (qL >= cR || qR <= cL) return;
    propagate(cN);
    int mid = (cL + cR) / 2;
    update(qL, qR, qV, cL, mid, cN*2);
    update(qL, qR, qV, mid, cR, cN*2+1);
    rtmax[cN] = max(rtmax[cN*2], rtmax[cN*2+1]);
}

ll querymax(int qL, int qR, int cL=1, int cR=MAXN+1, int cN=1) {
    if (qL <= cL && cR <= qR) {
        return rtmax[cN];
    }
    if (qL >= cR || qR <= cL) return 0;
    propagate(cN);
    int mid = (cL + cR) / 2;
    return max(querymax(qL, qR, cL, mid, cN*2),
                querymax(qL, qR, mid, cR, cN*2+1));
}

bool isRight[MAXN+5];
int val[MAXN+5];
vector<int> buildOrder;

set<int> sortedLefts;

void removeLeft(int plc) {
    int prv = *prev(sortedLefts.find(plc));
    update(1, plc, val[plc]-val[prv]);
    auto nxtIt = next(sortedLefts.find(plc));
    if (nxtIt != sortedLefts.end()) {
        int nxt = *nxtIt;
        update(1, nxt, -(val[plc]-val[prv]));
    }
    sortedLefts.erase(plc);
}

void insertLeft(int plc) {
    int prv = *prev(sortedLefts.lower_bound(plc));
    update(1, plc, -(val[plc]-val[prv]));
    auto nxtIt = sortedLefts.upper_bound(plc);
    if (nxtIt != sortedLefts.end()) {
        int nxt = *nxtIt;
        update(1, nxt, (val[plc]-val[prv]));
    }
    sortedLefts.insert(plc);
}

ll getAns() {
    // right contribution:
    ll ans = max(0ll, querymax(1, MAXN+1));
    // left contribution. Reminder: there will always be a sentinel at the end.
    ans += val[*prev(sortedLefts.end())];
    return ans;
}

int main() {
    int N, D;
    scanf("%d %d", &N, &D);
    FO(i,1,N+1) {
        char d; scanf(" %c", &d);
        if (d == 'R') isRight[i] = true;
    }
    FO(i,1,N+1) {
        scanf("%d", &val[i]);
    }
    vector<bool> deleted(N+1, false);
    FO(i,0,D) {
        int c; scanf("%d", &c);
        buildOrder.push_back(c);
        deleted[c] = true;
    }
    reverse(begin(buildOrder), end(buildOrder));
    // Sentinal values:
    val[MAXN+1] = INF;
    sortedLefts.insert(0);

    FO(i,1,N+1) {
        if (deleted[i]) continue;
        if (!isRight[i]) {
            if (val[*prev(sortedLefts.lower_bound(i))] < val[i]) {
                insertLeft(i);
            }
        } else {
            update(i, i+1, val[i]);
        }
    }
    vector<ll> allAns;
    allAns.push_back(getAns());
    for (int cB : buildOrder) {
        if (!isRight[cB]) {
            if (val[*prev(sortedLefts.lower_bound(cB))] < val[cB]) {
                while (true) {
                    auto nxtIt = sortedLefts.upper_bound(cB);
                    if (nxtIt == sortedLefts.end() || val[*nxtIt] > val[cB]) break;
                    removeLeft(*nxtIt);
                }
                insertLeft(cB);
            }
        } else {
            update(cB, cB+1, val[cB]);
        }
        allAns.push_back(getAns());
    }
    reverse(begin(allAns), end(allAns));
    for (ll a : allAns) {
        printf("%lld\n", a);
    }
}
