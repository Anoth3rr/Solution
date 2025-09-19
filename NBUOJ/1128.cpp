#include<stdio.h>
#include<string.h>

int main() {
    int n, idx = 0, cur = 0;
    int primes[100010], vis[100010];
    memset(vis, 0, sizeof(vis));
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) primes[idx++] = i;
        for (int j = 0; primes[j] <= n / i; ++j) {
            vis[primes[j]*i] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    while (cur < idx) {
        if (n == primes[cur]) {
            printf("%d\n", n);
            break;
        }
        else if (n % primes[cur] == 0) {
            printf("%d ", primes[cur]);
            n /= primes[cur];
        }
        else cur++;
    }
    return 0;
}
