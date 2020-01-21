#include <bits/stdc++.h>
using namespace std;

#define FO(i,a,b) for (int i = (a); i < (b); i++)
typedef long long ll;

const int MAXD = 1000;

int R, C, gr[MAXD][MAXD];

int dograffiti(const vector<int> &costs) {
    vector<int> dp(costs.size(), 0);
    for (unsigned int i = 1; i < costs.size(); i++) {
        dp[i] = (i == 1 ? 0 : dp[i-2]) + max(0, costs[i-1] + costs[i]);
        dp[i] = max(dp[i], dp[i-1]);
    }
    return dp[costs.size()-1];
}

int main() {
    scanf("%d %d", &R, &C);
    FO(r,0,R) FO(c,0,C) scanf("%d", &gr[r][c]);
    int ans = 0;
    FO(r,0,R) {
        vector<int> costs;
        FO(c,0,C) costs.push_back(gr[r][c]);
        ans += dograffiti(costs);
    }
    FO(c,0,C) {
        vector<int> costs;
        FO(r,0,R) costs.push_back(gr[r][c]);
        ans += dograffiti(costs);
    }
    printf("%d\n", ans);
    return 0;
}
