#include<stdio.h>
#include<math.h>

bool isPrime(int t) {
	if (t == 1)
		return false;
	for (int i = 2; i <= sqrt(t); ++i)
		if (t % i == 0)
			return false;
	return true;
}

int main() {
	int k1, k2, ans = 0, Ans[1010];
	scanf("%d%d", &k1, &k2);
	for (int i = k1; i <= k2; ++i)
		if (isPrime(i))
			Ans[ans++] = i;
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