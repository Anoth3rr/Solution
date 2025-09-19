#include<stdio.h>

int main() {
    int mx = -1, mn = 0x3f3f3f3f, t;
    for (int i = 1; i <= 10; ++i) {
        scanf("%d", &t);
        mx = t > mx ? t : mx;
        mn = t < mn ? t : mn;
    }
    printf("%d\n%d\n", mx, mn);
    return 0;
}