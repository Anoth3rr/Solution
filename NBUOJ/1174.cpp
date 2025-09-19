#include<stdio.h>
#include<math.h>

const int maxn = 100010;

bool isprime(int n) {
    for (int i = 2; i <= sqrt(n); ++i)
        if (n % i == 0) return false;
    return true;
}

bool find(int *a, int len, int key) {
    int l = 0, r = len;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (a[mid] == key) return true;
        else if (a[mid] > key) r = mid - 1;
        else l = mid + 1;
    }
    return false;
}

int prime[maxn], cnt = -1;

int main() {
    for (int i = 2; i <= maxn; ++i) if (isprime(i)) prime[++cnt] = i;
    int n;
    scanf("%d", &n);
    for (int i = 0; i <= cnt; ++i) {
        if (find(prime, cnt, n - prime[i])) {
            printf("%d=%d+%d\n", n, prime[i], n - prime[i]);
            return 0;
        }
    }
    return 0;
}