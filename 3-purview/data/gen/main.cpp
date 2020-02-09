#include "random.h"
#include "purview.h"
#include "bounds.h"

int main() {
    initialiseGenerator(79223);
    order(pointIn(MAX_N), MAX_N*0.01).printCase("order-RL.in");
    order(pointOut(MAX_N), MAX_N*0.01).printCase("order-LR.in");

    middleCase(circle(MAX_N), MAX_F).printCase("circle.in");
    middleCase(circle(MAX_N), 10).printCase("circle-flat.in");

    descendingSpecial(MAX_N).printCase("descending-special.in");
    
    valleyCase(MAX_N, false).printCase("valley-asc.in");
    valleyCase(MAX_N, true).printCase("valley-desc.in");

    randomCase(randomHalf(MAX_N)).printCase("random-half.in");
    randomCase(fill(MAX_N, 'L')).printCase("random-L.in");
    randomCase(fill(MAX_N, 'R')).printCase("random-R.in");
}
