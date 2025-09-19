#include<stdio.h>

int main() {
    int mx = -1, mxt = -1, mn = 0x3f3f3f3f, mnt, x;
    for (int i = 0; i < 10; ++i) {
        scanf("%d", &x);
        if (x > mx) {
            mx = x;
            mxt = i;
        }
        if (x < mn) {
            mn = x;
            mnt = i;
        }
    }
    printf("%d %d\n%d %d\n", mx, mxt, mn, mnt);
    return 0;
}