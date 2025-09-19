#include<stdio.h>

int main() {
	int f[50], n;
	f[1] = f[2] = 1;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		if (i == 1 || i == 2)
			f[i] = 1;
		else
			f[i] = f[i - 1] + f[i - 2];
		printf("%d ", f[i]);
	}
	printf("\n");
	return 0;
}
