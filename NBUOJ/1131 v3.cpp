#include<stdio.h>
#include<string.h>

int main() {
	int k1, k2, idx = 0, ans = 0, Ans[1010];
	int primes[1010], vis[1010];
	memset(vis, 0, sizeof(vis));
	scanf("%d%d", &k1, &k2);
	vis[0] = vis[1] = 1;
	for (int i = 2; i <= k2; ++i) {
		if (!vis[i]) primes[idx++] = i;
		for (int j = 0; primes[j] <= k2 / i; ++j) {
			vis[primes[j]*i] = 1;
			if (i % primes[j] == 0) break;
		}
	}
	for (int i = k1; i <= k2; ++i)
		if (!vis[i]) Ans[ans++] = i;
	printf("%d\n", ans);
	for (int i = 0; i < ans; ++i) {
		printf("%d", Ans[i]);
		if (i != ans - 1)
			printf(" ");
		else
			printf("\n");
	}
	return 0;
}