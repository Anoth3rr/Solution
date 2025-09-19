#include<stdio.h>

int main() {
    int n, ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) ans += (1 + i) * i / 2;
    printf("%d\n", ans);
    return 0;
}