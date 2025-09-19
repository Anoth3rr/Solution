#include<stdio.h>

int main() {
    char ch;
    while ((ch = getchar()) != '\n') {
        if ('a' <= ch && ch <= 'z')
            printf("%c", ch - 32);
        else if ('A' <= ch && ch <= 'Z')
            printf("%c", ch + 32);
        else
            printf("%c", ch);
    }
    return 0;
}