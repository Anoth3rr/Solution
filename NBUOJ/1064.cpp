#include<stdio.h>

const int maxn = 100010;

int main() {
    int a, max = -maxn;
    for (int i = 1; i <= 3; ++i) {
        scanf("%d", &a);
        max = max > a ? max : a;
    }
    printf("%d\n", max);
    return 0;
}