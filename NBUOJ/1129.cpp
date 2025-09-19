#include<stdio.h>
#include<math.h>

bool isPerfect(int n) {
	int sum = 0;
	for (int i = 1; i <= sqrt(n); ++i)
		if (n % i == 0) {
			if (i != n / i) sum += i + n / i;
			else sum += i;
		}
	return sum == 2 * n;
}

int main() {
	int a, b;
	bool flag = true;
	scanf("%d %d", &a, &b);
	for (int i = a; i <= b; ++i)
		if (isPerfect(i))
			printf("%d\n", i), flag = false;
	if (flag)
		printf("\n");
	return 0;
}
