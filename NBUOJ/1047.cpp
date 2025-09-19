#include<stdio.h>

int main() {
    char c;
    scanf("%c", &c);
    if ('a' <= c && c <= 'z') printf("%c\n", char(c - 32));
    else if ('A' <= c && c <= 'Z') printf("%c\n", char(c + 32));
    else printf("%c\n", c);
    return 0;
}