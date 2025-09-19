#include<stdio.h>

char trans(int n) {
	if (n <= 9) return n + '0';
	else return n - 10 + 'A';
}

void f(int n, int k) {
	if (n > k) f(n / k, k);
	printf("%c ", trans(n % k));
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	f(n, k);
	return 0;
}
