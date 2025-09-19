#include<stdio.h>

int main() {
    char c;
    scanf("%c", &c);
    if ('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z') printf("YES\n");
    else printf("NO\n");
    return 0;
}