#include<stdio.h>

int main() {
    int n;
    double ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        ans += 1.0 / i;
    printf("%.6f\n", ans);
    return 0;
}