#include <iostream>
#include <vector>

using namespace std;

const int MAX_R = 1223;
const int MAX_C = 1234;

int a[MAX_R][MAX_C];
int ans;

void step(int& x, int target) {
    if(x < target) {
        x+=2;
    } else if(x > target) {
        x-=2;
    }
}

const int INF = 1e5;

int minFinder(int r, int c, int er, int ec) {
    int m = a[r][c];
    while(r != er || c != ec) {
        step(r, er);
        step(c, ec);
        m = min(m, a[r][c]);
    }
    return m;
}

int main() {
    int R, C;
    cin >> R >> C;
    int total = 0;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> a[i+1][j+1];
            total += 2*a[i+1][j+1];
        }
    }

    if(R&1) {
        for(int i = 1; i <= C; i++) {
            total -= minFinder(1, i, R, i);
        }
    }
    if(C&1) {
        for(int i = 1; i <= R; i++) {
            total -= minFinder(i, 1, i, C);
        }
    }

    cout << total << "\n";
}
