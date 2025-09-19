#include<stdio.h>

int main() {
    int maxn, n = 0, i = 2, t = 0;
    scanf("%d", &maxn);
    while (n <= maxn) {
        n += i;
        i *= 2;
        ++t;
    }
    printf("Average=%.2f\n", 1.2 * n / t);
    return 0;
}