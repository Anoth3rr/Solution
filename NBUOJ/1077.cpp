#include<stdio.h>
#include<string.h>

int main() {
    char s[4];
    scanf("%s", &s);
    for (int i = 0; i < strlen(s); i++) {
        s[i] = (s[i] - '0' + 9) % 10 + '0';
    }
    printf("%c%c%c%c\n", s[2], s[3], s[0], s[1]);
    return 0;
}