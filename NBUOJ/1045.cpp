#include<stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int dis = n * n + m * m;
    if (dis > 100) printf("out\n");
    else if (dis == 100) printf("on\n");
    else printf("in\n");
    return 0;
}