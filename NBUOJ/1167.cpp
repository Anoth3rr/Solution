#include<stdio.h>

int main() {
	double sum = 0, n[10] = {0.1, 0.2, 0.5, 1, 2, 5, 10, 20, 50, 100};
	int a, b;
	do {
		scanf("%d%d", &a, &b);
		sum += n[a - 1] * b;
	}
	while (a != -1);
	printf("%.2f", sum);
	return 0;
}
