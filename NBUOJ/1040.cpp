#include<stdio.h>

int main() {
    int n, t, s1 = 0, s2 = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &t);
        if (t & 1) s1 += t;
        else s2 += t;
    }
    printf("%d\n%d\n", s1, s2);
    return 0;
}