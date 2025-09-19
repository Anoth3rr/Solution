#include<stdio.h>

int main() {
    double i, s;
    scanf("%lf%lf", &i, &s);
    printf("%.2f\n", s * (1 + i));
    return 0;
}