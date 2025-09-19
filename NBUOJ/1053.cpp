#include<stdio.h>

int main() {
    int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
    char s;
    s = getchar();
    while (s != '\n') {
        if ('a' <= s && s <= 'z' || 'A' <= s && s <= 'Z') ++n1;
        else if ('0' <= s && s <= '9') ++n2;
        else if (s == ' ') ++n3;
        else ++n4;
        s = getchar();
    }
    printf("%d %d %d %d\n", n1, n2, n3, n4);
    return 0;
}