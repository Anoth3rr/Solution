#include<stdio.h>

int main() {
	int a[11];
	for (int i = 1; i <= 10; ++i)
		scanf("%d", &a[i]);
	for (int i = 1; i <= 10; ++i)
		for (int j = 2; j <= 11 - i; ++j)
			if (a[j] > a[j - 1]) {
				a[j] = a[j] ^ a[j - 1];
				a[j - 1] = a[j] ^ a[j - 1];
				a[j] = a[j] ^ a[j - 1];
			}
	for (int i = 1; i <= 10; ++i)
		printf("%d ", a[i]);
	return 0;
}
