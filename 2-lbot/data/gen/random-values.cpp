// Generates a grid filled with random values
// First argument is rows, second columns, third is min value, fourth is max value
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int r = atoi(argv[1]), c = atoi(argv[2]);
	int mn = atoi(argv[3]), mx = atoi(argv[4]);
	assert(mn <= mx);
	printf("%d %d\n", r, c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			printf("%d%c", rnd.next(mn, mx), " \n"[j+1==c]);
		}
	}
}