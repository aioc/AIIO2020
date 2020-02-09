#include <vector>
#include <algorithm>
#include <cassert>

#include "random.h"
#include "bounds.h"

using namespace std;

struct Statue {
    char dir;
    int quota;
    
    Statue(char _dir, int _quota) : dir(_dir), quota(_quota) {}
    Statue (char _dir) : Statue(_dir, -1) {}
};

struct Testcase {
    vector<Statue> statues;
    // Zero indexed.
    vector<int> demolitions;
    
    uint count(char dir) {
        assert(dir == 'L' || dir == 'R');
        uint count = 0u;
        for(auto st: statues) {
            count += st.dir == dir;
        }
        return count;
    }

    void demolishTopDown() {
        demolitions = makerange(0, statues.size()-1);
        sort(begin(demolitions), end(demolitions), [this](int a, int b) {
            return statues[a].quota > statues[b].quota;
        });
    }

    void demolishOutToIn() {
        assert(statues.size() % 2 == 0);
        for(auto i = 0u; i < statues.size()/2; i++) {
            demolitions.push_back(i);
            demolitions.push_back(statues.size() - i - 1);
        }
    }

    void demolishRandom() {
        demolitions = randpermutation(0, statues.size());
    }

    void demolishValleySpecial(bool rev) {
        demolitions = makerange(0, statues.size()-1);
        reverse(demolitions.begin(), demolitions.end());
        // Demolish second half by ascending quota (which is the first half after reversing)
        sort(begin(demolitions), begin(demolitions) + demolitions.size()/2, [this, rev](int a, int b) {
            if(rev) {
                return (statues[a].quota > statues[b].quota);
            } else {
                return (statues[a].quota < statues[b].quota);
            }
        });
        // Demolish the first half randomly (which is the second half after reversing)
        random_shuffle(begin(demolitions) + demolitions.size()/2, end(demolitions), rndint);
    }

    void fill(char dir, vector<int> v) {
        //cerr << "Fill with " << dir << " thing of size " << v.size() << "\n";
        assert(count(dir) == v.size());
        int cur = 0;
        for(auto i = 0u; i < statues.size(); i++) {
            if(statues[i].dir == dir) {
                assert(statues[i].quota == -1);
                statues[i].quota = v[cur];
                cur++;
            }
        }
    }
    
    void printCase(string filename) {
        ofstream out(filename);
        out << statues.size() << " " << min(statues.size()-1, demolitions.size()) << "\n";
        for(auto st: statues) {
            out << st.dir;
        }
        out << "\n";

        bool first = true;
        for(auto st: statues) {
            if(!first) {
                out << " ";
            }
            first = false;
            out << st.quota;
        }
        out << "\n";
        
        first = true;
        // Skip demolition of the very last statue (as you can't have no statues)
        cerr << "Writing for " << filename << ". Statues: " << statues.size() << " demos " << demolitions.size() << "\n";
        for(auto i = 0u; i < min(statues.size()-1, demolitions.size()); i++) {
            auto x = demolitions[i];
            if(!first) {
                out << " ";
            }
            first = false;
            out << x+1; // Change from 0-index to 1-index for output.
        }
    }
};

vector<Statue> alternating(int N, char begin) {
    vector<Statue> v;
    for(int i = 0; i < N; i++) {
        v.emplace_back(((begin == 'L') ^ i) ? 'L': 'R');
    }
    return v;
}

vector<Statue> pointIn(int N) {
    assert(N%2 == 0);
    vector<Statue> v;
    for(int i = 0; i < N/2; i++) {
        v.emplace_back('R');
    }
    for(int i = 0; i < N/2; i++) {
        v.emplace_back('L');
    }
    return v;
}

vector<Statue> pointOut(int N) {
    assert(N%2 == 0);
    vector<Statue> v;
    for(int i = 0; i < N/2; i++) {
        v.emplace_back('L');
    }
    for(int i = 0; i < N/2; i++) {
        v.emplace_back('R');
    }
    return v;
}

vector<Statue> randomHalf(int N) {
    auto v = pointIn(N);
    random_shuffle(begin(v), end(v), rndint);
    return v;
}

vector<Statue> circle(int N) {
    vector<Statue> v;
    for(int i = 0; i < N; i++) {
        v.emplace_back(randdouble(0, 1) <= (double)i/(double)N ? 'L' : 'R');
    }
    return v;
}

vector<Statue> fill(int size, char dir) {
    vector<Statue> v;
    for(int i = 0; i < size; i++) {
        v.emplace_back(dir);
    }
    return v;
}

void fillValley(Testcase& t, uint maxValue=MAX_F) {
    int R = t.count('R');
    t.fill('R', randdesc(R, MIN_F, maxValue));
    int L = t.count('L');
    t.fill('L', randasc(L, MIN_F, maxValue));
}

Testcase order(vector<Statue> v, int cut) {
    Testcase t;
    t.statues = v;
    fillValley(t);

    for(int i = 0; i < cut; i++) {
        int idx = randint(t.statues.size());
        t.statues[idx].quota /= 2;
        t.statues[idx].quota++; // To make sure it isn't 0 at the end.
    }
    
    t.demolishTopDown();

    return t;
}

Testcase middleCase(vector<Statue> v, int maxValue) {
    Testcase t;
    t.statues = v;
    fillValley(t, maxValue);

    t.demolishOutToIn();
    return t;
}

Testcase descendingSpecial(int N) {
    auto v = randomHalf(N);
    Testcase t;
    t.statues = v;
    fillValley(t);
    // Set the smallest L and smallest R to MAX_F.
    for(auto it = t.statues.begin(); it != t.statues.end(); it++) {
        if(it->dir  == 'L') {
            it->quota = MAX_F;
            break;
        }
    }
    for(auto it = t.statues.rbegin(); it != t.statues.rend(); it++) {
        if(it->dir  == 'R') {
            it->quota = MAX_F;
            break;
        }
    }
    t.demolishRandom();
    return t;
}

Testcase randomCase(vector<Statue> v) {
    Testcase t;
    t.statues = v;
    //cerr << "Attempting random\n";
    t.fill('R', randvector(t.count('R'), MIN_F, MAX_F));
    t.fill('L', randvector(t.count('L'), MIN_F, MAX_F));
    t.demolishRandom();
    return t;
}

vector<int> valleyVector(int N) {
    assert(N%2 == 0);
    auto v1 = randdesc(N/2, MIN_F, MAX_F);
    auto v2 = randasc(N/2, MIN_F, MAX_F);
    v1.insert(v1.end(), v2.begin(), v2.end());
    return v1;
}

Testcase valleyCase(int N, bool reverse) {
    vector<int> vL = valleyVector(N/2);
    vector<int> vR = valleyVector(N/2);

    //cerr << "Attempting valley case\n";

    Testcase t;
    for(auto i = 0u; i < vL.size(); i++) {
        t.statues.emplace_back('L', vL[i]);
        t.statues.emplace_back('R', vR[i]);
    }

    t.demolishValleySpecial(reverse);
    return t;
}
