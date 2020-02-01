// Generates a grid where odd rows are negative, even rows positive, or the other way around
// First argument is rows, second columns
#include "testlib.h"
#include <bits/stdc++.h>
#define MIN_VALUE -1000
#define MAX_VALUE 1000
using namespace std;
int type;
int val(int i) {
	int parity = i%2;
	if (parity == type) return rnd.next(MIN_VALUE, 0);
	else return rnd.next(0, MAX_VALUE);
}
int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int r = atoi(argv[1]), c = atoi(argv[2]);
	type = rnd.next(2);
	printf("%d %d\n", r, c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			printf("%d ", val(i));
		}
		printf("\n");
	}
}