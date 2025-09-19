#include<stdio.h>

int main() {
    double n, t = 45;
    int cnt = 0;
    scanf("%lf", &n);
    while (t <= n) t *= 1.01, cnt++;
    printf("%d\n", 1980 + cnt);
    return 0;
}