#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    if (n >= 30)
        printf("%.2f\n", n * 48.0);
    else
        printf("%.2f\n", n * 50.0);
    return 0;
}