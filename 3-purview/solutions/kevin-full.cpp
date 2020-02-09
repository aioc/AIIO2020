#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAX_N = 1e5+5;
const int INF = 1e9+5;

int N, D;
string S;

struct rangetree {
    int l, r;
    rangetree *lc, *rc;
    int maxv;
    int dirty;


    rangetree(int _l, int _r) : l(_l), r(_r) {
        maxv = -INF;
        dirty = 0;
        if(l != r) {
            int m = (l+r)/2;
            lc = new rangetree(l, m);
            rc = new rangetree(m+1, r);
        }
    }

    void addToRange(int ql, int qr, int dv) {
        if(l == 1 && r == N) {
            //cerr << "Range " << ql << " " << qr <<" At " << l << " " << r << " dv: " << dv << "(" << dv - INF << ")\n";
        }
        if(l == 5 && r == 5) {
            //cerr << "Maxv at leaf 5 WAS " << maxv << " (" << -dv+INF << ")\n";
        }
        pushDirty();
        if(qr < l || r < ql) {
            return;
        } else if(ql <= l && r <= qr) {
            dirty += dv;
            maxv += dv;
        } else {
            lc->addToRange(ql, qr, dv);
            rc->addToRange(ql, qr, dv);
            maxv = max(lc->maxv, rc->maxv);
        }
        if(l == 1 && r == N) {
            //cerr << "Maxv is now " << maxv << "\n";
            //cerr << "lc rc" << lc->maxv << " " << rc->maxv << "\n";
        }
        if(l == 5 && r == 5) {
            //cerr << "Maxv at leaf 5 is " << maxv << "\n";
        }
    }

    bool leaf() {
        return l == r;
    }

    void pushDirty() {
        if(!leaf()) {
            lc->maxv += dirty;
            rc->maxv += dirty;
            lc->dirty += dirty;
            rc->dirty += dirty;
        }
        dirty = 0;
    }
};

rangetree* rt;

struct statue {
    int height;
    int pos;
    
    statue(int h, int p): height(h), pos(p) {}

    bool operator<(const statue& oth) const {
        return pos < oth.pos;
    }
};

int delta[MAX_N];
int h[MAX_N];


set<statue> s;

void addToSet(statue st) {
    if(s.lower_bound(st)->height >= st.height) {
        ////cerr << "IGNORE\n";
        return;
    }
    s.insert(st);
    while(1) {
        auto at = s.find(st);
        at--;
        if(at->height <= st.height) {
            // Pop off smaller things to the left
            rt->addToRange(at->pos, N, -delta[at->pos]);
            s.erase(at);
        } else {
            // We're done popping, add the new statue.
            
            // Update the one just to our left
            if(at->pos != 0) {
                // Remove old delta
                rt->addToRange(at->pos, N, -delta[at->pos]);
                // Add new delta
                delta[at->pos] = -at->height + st.height;
                rt->addToRange(at->pos, N, delta[at->pos]);
            }

            at++; at++;
            // Subtract from all statues to the right, the delta
            // between this statue and the next one on the right.
            delta[st.pos] = -st.height + at->height;
            rt->addToRange(st.pos, N, delta[st.pos]);


            break;
        }
    }
}

int main() {
    cin >> N >> D >> S;

    for(int i = 1; i <= N; i++) {
        cin >> h[i];
    }

    // Convert deletions into additions, starting with no statues
    
    vector<int> deletions;
    set<int> deletionSet;
    for(int i = 0; i < D; i++) {
        int d;
        cin >> d;
        deletions.push_back(d);
        deletionSet.insert(d);
    }

    for(int i = 1; i <= N; i++) {
        if(deletionSet.find(i) == deletionSet.end()) {
            deletions.push_back(i);
        }
    }

    reverse(deletions.begin(), deletions.end());
    auto addition = deletions;

    // Add dummy bookends to the set
    s.emplace(INF, 0);
    s.emplace(0, N+1);

    // Initialize range tree
    rt = new rangetree(1, N);

    vector<int> ans;
    int maxR = 0;

    for(uint i = 0; i < deletions.size(); i++) {
        int idx = deletions[i];
        if(S[idx-1] == 'R') {
            //cerr << "---------- Processing R " << h[idx] << " at " << idx << "\n";
            statue st{h[idx], idx};
            maxR = max(maxR, st.height);
            addToSet(st);
        } else {
            //cerr << "---------- Processing L " << h[idx] << " at " << idx << "\n";
            // Add INF to undo the -INF on initializing the range tree
            rt->addToRange(idx, idx, INF + h[idx]);
        }
        ans.push_back(max(0, rt->maxv) + maxR);
        //cerr << "Ans " << ans[ans.size()-1] << " (Right " << maxR << " left " << rt->maxv << ")\n";
    }

    // Print only the last D values
    auto it = ans.rbegin();
    for(int i = 0; i < D+1; i++) {
        cout << *it << "\n";;
        it++;
    }
}
