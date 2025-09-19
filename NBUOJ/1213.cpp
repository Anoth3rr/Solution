#include<stdio.h>
#include<math.h>

int getSum(int n) {
	int sum = 0;
	for (int i = 1; i <= sqrt(n); ++i) {
		if (n % i == 0) {
			sum += i + n / i;
		}
	}
	return sum - n;
}

int main() {
	int a, b;
	scanf("%d%d", &a, &b);
	if (getSum(a) == b && getSum(b) == a)
		printf("1");
	else
		printf("0");
	return 0;
}
