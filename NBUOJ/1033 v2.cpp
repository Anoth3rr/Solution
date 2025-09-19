#include<stdio.h>

int main() {
    int n, p;
    scanf("%d", &n);
    while (n) {
        p = n % 10;
        n /= 10;
    }
    printf("%d\n", p);
    return 0;
}