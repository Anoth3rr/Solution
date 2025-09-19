#include<stdio.h>

int main() {
	double sum = 0, x;
	int cnt = 0;
	for (int i = 0; i < 10; ++i) {
		scanf("%lf", &x);
		if (x > 0) {
			sum += x;
			cnt++;
		}
	}
	printf("%.2f", sum / cnt);
	return 0;
}
