#include<stdio.h>

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			if (i + j <= (n + 1) / 2 || i + (n - j + 1) <= (n + 1) / 2 || (n - i + 1) + j <= (n + 1) / 2 || (n - i + 1) + (n - j + 1) <= (n + 1) / 2) printf(" ");
			else printf("*");
		printf("\n");
	}
	return 0;
}
