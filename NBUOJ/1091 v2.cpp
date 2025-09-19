#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    if (n & 1) printf("%d\n", (1 + n) * (n / 2 + 1) / 2 - (2 + n - 1) * (n / 2) / 2);
    else printf("%d\n", (1 + n - 1) * (n / 2) / 2 - (2 + n) * (n / 2) / 2);
    return 0;
}