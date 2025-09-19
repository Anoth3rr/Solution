#include<stdio.h>

int main() {
    double f;
    scanf("%lf", &f);
    printf("%.2f\n", 5 * (f - 32) / 9);
    return 0;
}