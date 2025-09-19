#include<stdio.h>
#define ull unsigned long long

int main() {
    int t;
    ull sum = 0, cur = 1;
    scanf("%d", &t);
    while (t--) {
        sum += cur;
        cur *= 2ll;
    }
    printf("%llu\n", sum);
    return 0;
}