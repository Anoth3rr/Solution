#include<stdio.h>
#define pi 3.14

int main() {
    double r;
    scanf("%lf", &r);
    printf("%.2f %.2f\n", pi * r * 2, pi * r * r);
    return 0;
}