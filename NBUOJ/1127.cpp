#include<stdio.h>
#include<math.h>

int main() {
	int n, sum = 0;
	scanf("%d", &n);
	for (int i = 1; i <= sqrt(n); ++i)
		if (n % i == 0) {
			if (i != n / i) sum += i + n / i;
			else sum += i;
		}
	sum -= n;
	if (sum == n) printf("yes\n");
	else printf("no\n");
	return 0;
}
