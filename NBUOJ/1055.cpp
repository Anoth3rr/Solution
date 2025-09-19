#include<stdio.h>
#define maxn 100010

int main() {
    char s[maxn], pre;
    int cnt = -1, ans = 0;
    while ((s[++cnt] = getchar()) != '\n');
    while (!(s[0] == '@' && cnt == 1)) {
        cnt = -1;
        while ((s[++cnt] = getchar()) != '\n');
        ans++;
    }
    printf("%d\n", ans);
    return 0;
}