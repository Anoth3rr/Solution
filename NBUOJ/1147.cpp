#include<stdio.h>

int main() {
	int n;
	double t, mx = -1, mn = 101, sum = 0;
	for (int i = 0; i < 8; ++i)
		scanf("%lf", &t), mx = (t > mx ? t : mx), mn = (t < mn ? t : mn), sum += t;
	printf("%.2f\n", (sum - mx - mn) / 6);
	return 0;
}
