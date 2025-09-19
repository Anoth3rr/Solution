#include<stdio.h>

int main() {
    double n;
    scanf("%lf", &n);
    if (5000 <= n)
        printf("%.2f\n", n * 0.8);
    else if (3000 <= n)
        printf("%.2f\n", n * 0.85);
    else if (1000 <= n)
        printf("%.2f\n", n * 0.9);
    else if (500 <= n)
        printf("%.2f\n", n * 0.95);
    else
        printf("%.2f\n");
    return 0;
}