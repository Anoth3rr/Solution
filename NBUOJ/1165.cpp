#include<stdio.h>

int main() {
	int n;
	int a[20], b[20];
	scanf("%d", &n);
	a[1] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j)
			b[j] = a[j] + a[j - 1], printf("%d ", b[j]);
		for (int j = 1; j <= i; ++j)
			a[j] = b[j];
		printf("\n");
	}
	return 0;
}
