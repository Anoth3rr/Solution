#include<stdio.h>

int main() {
    int n, t = 1;
    scanf("%d", &n);
    for (int i = 0; i <= n; ++i)
        printf("%d ", t), t *= 2;
    return 0;
}
