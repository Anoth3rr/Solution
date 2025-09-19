#include<stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d %d\n%d %d\n", n, m, m, n);
    return 0;
}

#include<stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d %d\n", n, m);
    int t = n;
    m = n;
    n = t;
    printf("%d %d\n", n, m);
    return 0;
}