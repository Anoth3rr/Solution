#include<stdio.h>

int main() {
    int n;
    double ans = 0;
    scanf("%d", &n);
    for (int i = 1; i < 2 * n; ++i)
        ans += 1.0 / i;
    printf("%.2f\n", ans);
    return 0;
}