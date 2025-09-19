#include<stdio.h>

int main() {
    char s[3];
    scanf("%s", &s);
    switch (s[0]) {
    case '+':
        printf("%d\n", s[1] + s[2]);
        break;
    case '-':
        printf("%d\n", s[1] - s[2]);
        break;
    }
    return 0;
}