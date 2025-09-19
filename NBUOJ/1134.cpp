#include<stdio.h>

int main() {
	int n;
	bool flag = true;
	scanf("%d", &n);
	for (int i = 0; i <= 9; ++i)
		for (int j = 0; j <= 9; ++j)
			for (int k = 0; k <= 9; ++k) {
				if (i * 101 + j * 20 + k * 101 == n)
					printf("a=%d,b=%d,c=%d\n", i, j, k), flag = false;
			}
	if (flag) printf("No Solution");
	return 0;
}