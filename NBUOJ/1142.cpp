#include<stdio.h>

int main() {
	double a, b, c;
	for (int i = 1; i <= 3; ++i) {
		scanf("%lf%lf%lf", &a, &b, &c);
		printf("%.1f\n", (a + b + c) / 3);
	}
	return 0;
}
