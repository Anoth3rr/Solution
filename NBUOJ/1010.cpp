#include<stdio.h>
#define pi 3.14

int main() {
    double r;
    scanf("%lf", &r);
    printf("%.2f\n", 4 * pi * r * r * r / 3);
    return 0;
}