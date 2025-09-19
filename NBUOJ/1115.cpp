#include<stdio.h>

int main() {
    int n, t = 2, sum = 0, cnt = 0;
    scanf("%d", &n);
    if (n <= 1) {
        printf("0.00\n");
        return 0;
    }
    while (sum + t <= n) {
        sum += t;
        t *= 2;
        cnt++;
    }
    printf("%.2f\n", sum * 0.4 / cnt);
    return 0;
}