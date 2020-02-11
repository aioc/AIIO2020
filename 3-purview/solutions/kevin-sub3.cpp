#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int N, D;
string S;

struct Statue {
    char dir;
    int quota;

    int deltaL;
    int offset;

    Statue(char _d, int _q) : dir(_d), quota(_q), deltaL(0), offset(0) {}
};

int ans;

vector<Statue> statues;

int main() {
    cin >> N >> D;
    cin >> S;
    for(int i = 0; i < N; i++) {
        int x;
        cin >> x;
        statues.emplace_back(S[i], x);
    }

    int maxL = 0;
    for(int i = 0; i < N; i++) {
        if(S[i] == 'L' && statues[i].quota > maxL) {
            statues[i].deltaL = statues[i].quota - maxL;
            maxL = statues[i].quota;
        }
    }
    
    int totalOffset = 0;
    for(int i = N-1; i >= 0; i--) {
        if(S[i] == 'R') {
            statues[i].offset = totalOffset;
        } else {
            totalOffset += statues[i].deltaL;
        }
    }

    vector<int> deletions;
    for(int i = 0; i < D; i++) {
        int x;
        cin >> x;
        x--;
        deletions.push_back(x);
    }

    set<int> deletionSet(deletions.begin(), deletions.end());
    for(int i = 0; i < N; i++) {
        if(S[i] == 'R' && deletionSet.find(i) == deletionSet.end()) {
            deletions.push_back(i);
        }
    }
    auto additions = deletions;
    reverse(begin(additions), end(additions));

    vector<int> ans{maxL};

    //cerr << "Max L is " << maxL << "\n";
    int maxR = 0;
    for(auto a: additions) {
        //cerr << "here we are at maxR = " << maxR << "\n";
        maxR = max(maxR, statues[a].quota - statues[a].offset);
        ans.push_back(maxL + maxR);
    }

    for(int i = 0; i < D+1; i++) {
        cout << ans[ans.size() - 1 - i] << "\n";
    }

}
