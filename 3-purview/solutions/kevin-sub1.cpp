#include <iostream>
#include <vector>

using namespace std;

int N, D;
string S;

struct Statue {
    char dir;
    int quota;

    Statue(char _d, int _q) : dir(_d), quota(_q) {}
};

int ans;

vector<Statue> statue;

void shuck() {
    vector<Statue> newStatue;
    for(auto x: statue) {
        if(x.quota != 0) {
            newStatue.push_back(x);
        }
    }
    statue = newStatue;
    /*
    cerr << "New size " << statue.size() << "\n";
    for(int i = 0; i < statue.size(); i++) {
        cerr << statue[i].dir;
    }
    cerr << "\n";
    for(int i = 0; i < statue.size(); i++) {
        cerr << statue[i].quota;
    }
    cerr << "\n";
    */
}

void decrement(int start, int dir, char X, int delta) {
    //cerr << "Decrement " << start << " " << dir << " " << X << " " << delta << "\n";
    for(int i = start; 0 <= i && i <= (int)statue.size(); i += dir) {
        if(statue[i].dir == X) {
            statue[i].quota += delta;
            statue[i].quota = max(0, statue[i].quota);
            //cerr << "Force down " << i << " (" << statue[i].quota << ")\n";
        }
    }
}

bool scrape() {
    //cerr << "Scrape()\n";
    for(auto i = 0u; i < statue.size(); i++) {
        if(statue[i].dir == 'L') {
            int delta = statue[i].quota;
            ans += delta;
            decrement(i,  1, 'L', -delta);
            decrement(i, -1, 'R', -delta);
            shuck();
            return true;
        }
    }
    return false;
}
int main() {
    cin >> N >> D;
    cin >> S;
    for(int i = 0; i < N; i++) {
        int x;
        cin >> x;
        statue.emplace_back(S[i], x);
    }

    while(scrape()) {}

    int most = 0;
    for(auto x: statue) {
        most = max(most, x.quota);
    }

    //cerr << ans << " + " << most << "\n";
    cout << ans + most << "\n";
}
