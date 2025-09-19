#include<stdio.h>

void sort(int* a, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j < n - i; ++j) {
			if (a[j - 1] < a[j]) {
				int tmp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = tmp;
			}
		}
	}
}

int main() {
	int a[3];
	for (int i = 0; i <= 2; ++i) {
		scanf("%d", &a[i]);
	}
	sort(a, 3);
	printf("%d %d %d\n", a[0], a[1], a[2]);
	return 0;
}