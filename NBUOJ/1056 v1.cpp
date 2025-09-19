#include<stdio.h>
#define maxn 100010

int main() {
    char s[maxn];
    char ch;
    int cnt = -1;
    int ans = 0;
    while ((s[++cnt] = getchar()) != '\n');
    ch = getchar();
    for (int i = 0; i < cnt; ++i)
        if (s[i] == ch)
            ans++;
    printf("%d\n", ans);
    return 0;
}