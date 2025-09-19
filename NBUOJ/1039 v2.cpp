#include<stdio.h>

int main() {
    int n, odd = 0, even = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        if (i & 1) odd += i;
        else even += i;
    }
    printf("%d\n%d\n", odd, even);
    return 0;
}