#include<stdio.h>
#define pi 3.14

int main() {
    double r, h;
    scanf("%lf%lf", &r, &h);
    printf("%.2f\n", 2 * pi * r * r + 2 * pi * r * h);
    return 0;
}