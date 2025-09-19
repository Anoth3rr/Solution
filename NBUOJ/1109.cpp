#include<stdio.h>

int main() {
    int n, t, sum = 0;
    while (scanf("%d", &n) != EOF) {
        sum = 0;
        for (int i = 0; i < n; ++i)
            scanf("%d", &t), sum += t;
        printf("%d\n", sum);
    }
    return 0;
}