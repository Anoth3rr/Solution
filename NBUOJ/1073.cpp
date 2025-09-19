#include<stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        printf("31\n");
    else if (m == 4 || m == 6 || m == 9 || m == 11)
        printf("30\n");
    else {
        if (n % 4 == 0 && n % 100 != 0 || n % 400 == 0)
            printf("29\n");
        else
            printf("28\n");
    }
    return 0;
}