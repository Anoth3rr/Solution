#include<stdio.h>

int main() {
    int n, t, cnta = 0, cntb = 0, cntc = 0;
    double ave = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &t);
        if (t > 0) cnta++;
        if (t < 0) cntb++;
        if (t == 0) cntc++;
    }
    printf("%d\n%d\n%d\n", cnta, cntb, cntc);
    return 0;
}