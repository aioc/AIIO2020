// Rotates a test case by swapping rows and columns
#include <bits/stdc++.h>
using namespace std;
int grid[1000][1000];
int main() {
	int r, c;
	scanf("%d%d", &r, &c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			scanf("%d", &grid[i][j]);
		}
	}
	printf("%d %d\n", c, r);
	for (int j = 0; j < c; j++) {
		for (int i = 0; i < r; i++) {
			printf("%d%c", grid[i][j], " \n"[i+1==r]);
		}
	}
}