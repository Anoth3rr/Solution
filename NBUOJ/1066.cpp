#include<stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    double a, b;
    b = (m - 2.0 * n) / 2;
    a = n - b;
    if (a < 0 || b < 0 || !m & 1 || a != int(a) || b != int(b))
        printf("NO answer\n");
    else
        printf("%.0f %.0f\n", a, b);
    return 0;
}