#include<stdio.h>

int main() {
    int mx = -1, t;
    for (int i = 0; i < 12; ++i)
        scanf("%d", &t), mx = t > mx ? t : mx;
    printf("%d\n", mx);
    return 0;
}