#include<stdio.h>

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		if (n & 1) {
			printf("0 0\n");
			return;
		}
		if ((n >> 1) & 1) printf("%d %d\n", (n >> 2) + 1, n >> 1);
		else printf("%d %d\n", n >> 2, n >> 1);
	}
	return 0;
}
