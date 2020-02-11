// Generates a grid filled with random values
// First argument is rows, second columns, third is min value, fourth is max value
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
	registerGen(argc, argv, 1);
	int r = stoi(argv[1]), c = stoi(argv[2]);

	printf("%d %d\n", r, c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			printf("%d%c", i+1, " \n"[j+1==c]);
		}
	}
}
