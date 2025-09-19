#include<stdio.h>

char toCapital(char c) {
    if ('a' <= c && c <= 'z') return c - 32;
    return c;
}

int main() {
    int a[200];
    for (int i = 0; i < 200; ++i) a[i] = 0;
    char c;
    while ((c = getchar()) != '\n')
        a[toCapital(c)]++;
    for (int i = 'A'; i <= 'Z'; ++i)
        if (a[i])
            printf("\'%c\':%d\n", i, a[i]);
    return 0;
}