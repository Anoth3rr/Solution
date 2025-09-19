#include<stdio.h>

int main() {
    int m, a[110], ans = 0;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) a[i] = 1;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= m; ++j)
            if (j % i == 0) a[j] = -a[j];
    for (int i = 1; i <= m; ++i)
        if (a[i] == -1) ans++;
    printf("%d\n", ans);
    for (int i = 1; i <= m; ++i)
        if (a[i] == -1) printf("%4d", i);
    printf("\n");
    return 0;
}
