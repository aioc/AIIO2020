// First two arguments are rows and columns, third argument is the value
// Sets all grid squares to the value
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
	int r = atoi(argv[1]), c = atoi(argv[2]);
	int value = atoi(argv[3]);
	printf("%d %d\n", r, c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			printf("%d ", value);
		}
		printf("\n");
	}
}