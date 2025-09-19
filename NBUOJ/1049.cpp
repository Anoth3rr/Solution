#include<stdio.h>

int main() {
    char c;
    scanf("%c", &c);
    if ('a' <= c && c <= 'z') printf("lower\n");
    else if ('A' <= c && c <= 'Z') printf("upper\n");
    else if ('0' <= c && c <= '9') printf("digit\n");
    else printf("other\n");
    return 0;
}