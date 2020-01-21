#include <bits/stdc++.h>
using namespace std;

#define FO(i,a,b) for (int i = (a); i < (b); i++)
typedef long long ll;

const int MAXN = 100000;
int N, D;
bool isRight[MAXN];
ll val[MAXN];
bool deleted[MAXN];

ll getAns() {
    ll placedSoFar = 0;
    ll ans = 0;
    vector<ll> placements(MAXN, 0);
    FO(i,0,N) {
        if (deleted[i]) continue;
        if (isRight[i]) continue;
        ll toPlace = max(0ll, val[i] - placedSoFar);
        placements[i] = toPlace;
        placedSoFar += toPlace;
        ans += toPlace;
    }
    placedSoFar = 0;
    for (int i = N-1; i >= 0; i--) {
        if (deleted[i]) continue;
        if (isRight[i]) {
            ll toPlace = max(0ll, val[i] - placedSoFar);
            placements[i] = toPlace;
            ans += toPlace;
        }
        placedSoFar += placements[i];
    }
    return ans;
}

int main() {
    scanf("%d %d", &N, &D);
    // Comment out if you want to use as a brute force in a diff:
    assert(D == 0);
    FO(i,0,N) {
        char d; scanf(" %c", &d);
        if (d == 'R') isRight[i] = true;
    }
    FO(i,0,N) {
        scanf("%d", &val[i]);
    }
    printf("%lld\n", getAns());
    // TEMPORARY:
    FO(d,0,D) {
        int plc; scanf("%d", &plc); plc--;
        deleted[plc] = true;
        printf("%lld\n", getAns());
    }
    return 0;
}
