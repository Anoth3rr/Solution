#include<stdio.h>

int main() {
    double e = 1, t = 1;
    int n;
    scanf("%d", &n);
    if (n >= 9) printf("2.718282\n");
    else {
        for (int i = 1; i <= n; ++i) {
            t *= i;
            e += 1 / t;
        }
        printf("%.6f\n", e);
    }
    return 0;
}