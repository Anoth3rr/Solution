#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    while (n) {
        if (n % 10) printf("%d", n % 10);
        n /= 10;
    }
    return 0;
}