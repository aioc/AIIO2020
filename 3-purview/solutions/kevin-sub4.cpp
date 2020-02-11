#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>

using namespace std;

int N, D;
string S;
vector<int> quotas;

int maxL;
multiset<int> gvs;

struct group {
    int curL;
    int maxR;

    int insVal = -1;

    group(int _c, int _r) : curL(_c), maxR(_r) {}

    int score() {
        if(insVal == -1) {
            //cerr << "maxR maxL curL " << maxR << " " << maxL << " " << curL << "\n";
            insVal = max(0, maxR + - maxL + curL);
        }
        return insVal;
    }

    void erase() {
        //cerr << "Erase "  << score() << "\n";
        gvs.erase(gvs.find(score()));
    }

    void insert() {
        //cerr << "Insert "  << score() << "\n";
        gvs.insert(score());
    }
};


int main() {
    cin >> N >> D;
    cin >> S;
    for(int i = 0; i < N; i++) {
        int x;
        cin >> x;
        quotas.push_back(x);
    }

    vector<int> ans;

    stack<group> s;

    gvs.insert(0);
    int maxRPopped = 0;
    for(int i = N-1; i >= 0; i--) {
        //cerr << "Add statue " << i+1 << "\n";
        if(S[i] == 'L') {
            maxL = max(maxL, quotas[i]);

            while(!s.empty()) {
                auto g = s.top();
                if(quotas[i] >= g.curL) {
                    maxRPopped = max(maxRPopped, g.maxR);
                    g.erase();
                    s.pop();
                } else {
                    break;
                }
            }
            group g(quotas[i], maxRPopped);
            g.insert();
            s.push(g);

            maxRPopped = 0;
        } else {
            // S[i] == 'R'
            maxRPopped = max(maxRPopped, quotas[i]);
        }
        int last = max(0, maxRPopped - maxL);
        //cerr << "Ans " << max(*gvs.rbegin(), last) + maxL << "\n";
        ans.push_back(max(*gvs.rbegin(), last) + maxL);
    }

    for(auto it = ans.rbegin(); it != ans.rend(); it++) {
        cout << *it << "\n";
    }
}
