#include<stdio.h>

int gcd(int a, int b) {
    if (a % b == 0) return b;
    return gcd(b, a % b);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int g = gcd(n, m);
    printf("%d %d\n", g, n * m / g);
    return 0;
}