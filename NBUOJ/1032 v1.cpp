#include<stdio.h>
#include<string.h>
#define maxn 100010

int main() {
    char s[maxn];
    int ans = 0;
    scanf("%s", &s);
    for (int i = 0; i < strlen(s); ++i)
        ans += s[i] - '0';
    printf("%d\n", ans);
    return 0;
}