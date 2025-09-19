#include<stdio.h>

int main() {
    int n, f = 1, t = 1;
    double ans = 0;
    scanf("%d", &n);
    if (n >= 9) printf("0.67\n");
    else {
        for (int i = 1; i <= n; ++i) {
            ans += 1.0 / t * f;
            t *= 2;
            f = -f;
        }
        printf("%.2f\n", ans);
    }
    return 0;
}