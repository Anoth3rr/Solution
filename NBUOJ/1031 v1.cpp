#include<stdio.h>
#include<string.h>
#define maxn 100010

int main() {
    char s[maxn];
    bool flag = true;
    scanf("%s", &s);
    for (int i = strlen(s) - 1; i >= 0, --i) {
        if (s[i] == '0' && flag) {
            continue;
        }
        else {
            printf("%c", s[i]);
            if (flag) flag = false;
        }
    }
    printf("\n");
    return 0;
}