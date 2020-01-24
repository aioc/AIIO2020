#include <iostream>
#include <vector>

using namespace std;

const int MAX_R = 1223;
const int MAX_C = 1234;

int a[MAX_R][MAX_C];
int ans;

int solve(vector<int> x) {
    vector<int> dp(x.size(), 0);
    for(int i = 0; i < x.size(); i++) {
        dp[i] = i ? dp[i-1] : 0;
        if(i >= 1) {
            dp[i] = max(dp[i], (i == 1 ? 0 : dp[i-2]) + x[i] + x[i-1]);
        }
    }
    return dp[x.size()-1];
}

int main() {
    int R, C;
    cin >> R >> C;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> a[i][j];
        }
    }

    for(int i = 0; i < R; i++) {
        vector<int> x;
        for(int j = 0; j < C; j++) {
            x.push_back(a[i][j]);
        }
        ans += solve(x);
    }

    for(int i = 0; i < C; i++) {
        vector<int> x;
        for(int j = 0; j < R; j++) {
            x.push_back(a[j][i]);
        }
        ans += solve(x);
    }

    cout << ans << "\n";
}
