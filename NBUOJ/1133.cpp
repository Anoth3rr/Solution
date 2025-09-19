#include<stdio.h>

bool check(int n) {
	int x = n / 100, y = n % 100;
	return (x + y) * (x + y) == n;
}

int main() {
	int a, b;
	scanf("%d%d", &a, &b);
	for (int i = a; i <= b; ++i)
		if (check(i)) printf("%d\n", i);
	return 0;
}
