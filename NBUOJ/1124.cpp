#include<stdio.h>

typedef long long ll;

int main() {
    int n;
    ll f[50000];
    f[1] = f[2] = 1;
    scanf("%d", &n);
    for (int i = 3; i <= n; ++i)
        f[i] = f[i - 1] + f[i - 2];
    printf("%lld", f[n]);
    return 0;
}