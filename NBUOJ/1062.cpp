#include<stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    printf("%d %d\n", n > m ? m : n, n > m ? n : m);
    return 0;
}