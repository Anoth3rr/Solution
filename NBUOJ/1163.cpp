#include<stdio.h>

const int maxn = 100010;

int main() {
    int cnt1[maxn] = {0}, cnt2[maxn] = {0}, t, n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &t), cnt1[t]++;
    for (int i = 0; i < n; ++i) scanf("%d", &t), cnt2[t]++;
    bool flag = true;
    for (int i = 0; i < maxn; ++i) if (cnt1[i] && cnt2[i]) printf("%d\n", i), flag = false;
    if (flag) printf("failure\n");
    return 0;
}