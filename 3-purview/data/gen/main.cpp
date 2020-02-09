#include <vector>

#include "random.h"
#include "purview.h"
#include "bounds.h"

using namespace std;

int main() {
    initialiseGenerator(79223);
    for(auto N: vector<int>{MAX_N, SMALL_N}) {
        order(pointIn(N), N*0.01).printCases("order-RL.in");
        order(pointOut(N), N*0.01).printCases("order-LR.in");

        middleCase(circle(N), MAX_F).printCases("circle.in");
        middleCase(circle(N), 10).printCases("circle-flat.in");

        descendingSpecial(N).printCases("descending-special.in");
        
        valleyCase(N, false).printCases("valley-asc.in");
        valleyCase(N, true).printCases("valley-desc.in");

        randomCase(randomHalf(N)).printCases("random-half.in");
        randomCase(fill(N, 'L')).printCases("random-L.in");
        randomCase(fill(N, 'R')).printCases("random-R.in");
    }
}
