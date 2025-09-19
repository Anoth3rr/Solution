#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    if (n % 35 == 0)
        printf("yes\n");
    else
        printf("no\n");
    return 0;
}