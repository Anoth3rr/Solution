#include<stdio.h>

int main() {
    char s;
    int cnt = 0;
    s = getchar();
    while (s != '\n') {
        if ('0' <= s && s <= '9') ++cnt;
        s = getchar();
    }
    printf("%d\n", cnt);
    return 0;
}