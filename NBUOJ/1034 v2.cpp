#include<stdio.h>

int main() {
    int n, cnt = 0;
    scanf("%d", &n);
    while (n) {
        n /= 10;
        cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}