#include<stdio.h>

int main() {
    int t;
    double ans = 0, n = 1, m = 2, p;
    scanf("%d", &t);
    while (t--) {
        ans += m / n;
        p = n + m;
        n = m;
        m = p;
    }
    printf("%.6f\n", ans);
    return 0;
}