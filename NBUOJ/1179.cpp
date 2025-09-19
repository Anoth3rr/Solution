#include<stdio.h>

int main() {
	int n;
	double sum = 0, mx = -1, mn = 0x3f3f3f3f, data;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%lf", &data);
		sum += data;
		mx = data > mx ? data : mx;
		mn = data < mn ? data : mn;
	}
	sum -= mx + mn;
	printf("%.2f\n", sum / (n - 2));
	return 0;
}
