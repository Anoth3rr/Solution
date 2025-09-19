#include<stdio.h>

int main() {
	int a[11];
	for (int i = 1; i <= 10; ++i)
		scanf("%d", &a[i]);
	for (int i = 1; i <= 10; ++i)
		printf("%d ", a[11 - i]);
	return 0;
}
