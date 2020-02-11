#include <iostream>
#include <vector>

using namespace std;

int a[5][5];
char facing[5][5];
const int INF = 1e9;

const string cand = "pqbd";

bool match(char x, string s) {
    return s.find(x) != string::npos;
}

int solve() {
    int ans = 0;
    for(int r = 1; r <= 3; r++) {
        for(int c = 1; c <= 3; c++) {
            char _l = facing[r][c];
            char _r = facing[r][c+1];
            if(match(_l, "pb") && match(_r, "dq")) {
                ans +=  max(a[r][c] + a[r][c+1], 0);
            }
        }
    }

    for(int r = 1; r <= 3; r++) {
        for(int c = 1; c <= 3; c++) {
            char _u = facing[r][c];
            char _d = facing[r+1][c];
            if(match(_u, "pq") && match(_d, "db")) {
                ans +=  max(a[r][c] + a[r+1][c], 0);
            }
        }
    }
    return ans;
}

int main() {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            a[i][j] = -INF;
        }
    }
    int R, C;
    cin >> R >> C;
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            cin >> a[i][j];
        }
    }

    int ans = 0;

    for(auto d1: cand)
    for(auto d2: cand)
    for(auto d3: cand)
    for(auto d4: cand)
    for(auto d5: cand)
    for(auto d6: cand)
    for(auto d7: cand)
    for(auto d8: cand)
    for(auto d9: cand) {
        facing[1][1] = d1;
        facing[1][2] = d2;
        facing[1][3] = d3;
        facing[2][1] = d4;
        facing[2][2] = d5;
        facing[2][3] = d6;
        facing[3][1] = d7;
        facing[3][2] = d8;
        facing[3][3] = d9;
        ans = max(ans, solve());
    }

    cout << ans << "\n";
}
