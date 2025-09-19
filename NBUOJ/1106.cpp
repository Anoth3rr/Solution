#include<stdio.h>

int main() {
    int n, q, i, e;
    while (scanf("%d", &n) != EOF) {
        q = 0;
        if (n <= 0) q = 0;
        else if (n == 1 || n == 2) q = 1;
        else {
            if (n & 1) n--;
            i = 2;
            e = 0;
            while (1) {
                while (n % i == 0) {
                    e = 1;
                    n = n / i;
                    i = i + 1;
                }
                if (n == 1) {
                    q = 1;
                    break;
                }
                if (i > n || e == 0)
                    break;
                if (e == 1) {
                    n--;
                    e = 0;
                }
            }
        }
        if (q == 1) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}