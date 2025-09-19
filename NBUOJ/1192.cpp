#include<stdio.h>

int main() {
	int n, node[1010];
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		node[i] = i + 1;
	}
	node[n] = 1;
	int pre = n, p = 1, cnt = 0;
	while (p != pre) {
		if (cnt == 2) node[pre] = node[p], cnt = -1;
		cnt++;
		pre = p;
		p = node[p];
	}
	printf("%d\n", p);
	return 0;
}
