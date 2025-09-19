#include<stdio.h>

int main() {
    int m, n, a;
    scanf("%d%d", &m, &n);
    a = (n - 2 * m) / 2;
    printf("%d %d\n", m - a, a);
    return 0;
}