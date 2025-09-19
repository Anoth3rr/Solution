#include<stdio.h>

int main() {
    int n, ans = 0, t = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        t = 1;
        for (int j = 1; j <= i; ++j)
            t *= j;
        ans += t;
    }
    printf("%d\n", ans);
    return 0;
}