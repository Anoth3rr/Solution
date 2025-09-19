#include<stdio.h>

int main() {
    char s;
    int cnt = 0;
    s = getchar();
    while (s != '\n') {
        if ('a' <= s && s <= 'z' || 'A' <= s && s <= 'Z') ++cnt;
        s = getchar();
    }
    printf("%d\n", cnt);
    return 0;
}