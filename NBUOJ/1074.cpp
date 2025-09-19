#include<stdio.h>

int main() {
    int y, m, d, yy, mm, dd;
    scanf("%d%d%d%d%d%d", &y, &m, &d, &yy, &mm, &dd);
    printf("%d", yy - y - (mm < m || mm == m && dd < d));
    return 0;
}