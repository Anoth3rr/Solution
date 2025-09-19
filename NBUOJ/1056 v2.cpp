#include<stdio.h>

int main() {
    int a[200] = {0};
    char ch;
    while ((ch = getchar()) != '\n')
        a[ch]++;
    printf("%d\n", a[getchar()]);
    return 0;
}