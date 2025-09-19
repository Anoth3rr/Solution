#include<stdio.h>

const int maxn = 100010;

int main() {
    char s[maxn];
    int cnt = -1;
    while ((s[++cnt] = getchar()) != '\n');
    printf("%s", s);
    return 0;
}