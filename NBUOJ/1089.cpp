#include<stdio.h>

int main() {
    int n, m, cnt = 0;
    scanf("%d%d", &n, &m);
    for (int i = n; i <= m; ++i)
        if (i % 3 != 0)
            if (cnt < 4) printf("%d ", i), cnt++;
            else printf("%d\n", i), cnt = 0;
    return 0;
}