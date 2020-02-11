#include <iostream>
#include <vector>

using namespace std;

const int MAX_R = 1223;

int ans;

int solve(vector<int> x) {
    vector<int> dp(x.size(), 0);
    for(int i = 0; i < (int)x.size(); i++) {
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

    int ans = 0;
    vector<int> a;
    for(int i = 0; i < C; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    ans += solve(a);

    vector<int> b;
    for(int i = 0; i < C; i++) {
        int x;
        cin >> x;
        b.push_back(x);
    }
    ans += solve(b);

    for(uint i = 0; i < a.size(); i++) {
        ans += max(0, a[i] + b[i]);
    }
    cout << ans << "\n";
}
