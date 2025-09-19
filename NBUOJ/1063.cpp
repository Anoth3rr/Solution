#include<stdio.h>

int main() {
    char n, m;
    scanf("%c%c", &n, &m);
    printf("%c %c\n", n > m ? m : n, n > m ? n : m);
    return 0;
}