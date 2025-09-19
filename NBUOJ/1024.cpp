#include<stdio.h>

int main() {
    double x;
    scanf("%lf", &x);
    printf("%.1f\n", 2 * x * x + x + 8);
    return 0;
}