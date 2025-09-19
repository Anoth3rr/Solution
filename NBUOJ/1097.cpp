#include<stdio.h>

int main() {
    int n, a, t = 0, ans = 0;
    scanf("%d%d", &n, &a);
    t = a;
    for (int i = 1; i <= n; ++i)
        ans += t, t = t * 10 + a;
    printf("%d\n", ans);
    return 0;
}