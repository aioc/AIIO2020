// Takes in two arguments + the test case from stdin
// Reduces r to min(r, maxr), c to min(c, maxc)
#include <bits/stdc++.h>
using namespace std;
int grid[1000][1000];
int main(int argc, char* argv[]) {
	int maxr = atoi(argv[1]), maxc = atoi(argv[2]);
	int r, c;
	scanf("%d%d", &r, &c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			scanf("%d", &grid[i][j]);
		}
	}
	r = min(r, maxr);
	c = min(c, maxc);
	printf("%d %d\n", r, c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			printf("%d%c", grid[i][j], " \n"[j+1==c]);
		}
	}
}