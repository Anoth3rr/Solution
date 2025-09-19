#include<stdio.h>

int main() {
    double n, a, b;
    scanf("%lf%lf%lf", &n, &a, &b);
    if (a == 90)
        a = 5.14;
    else if (a == 93)
        a = 5.54;
    else if (a == 97)
        a = 5.90;
    else if (a == 0)
        a = 5.13;
    if (b == 1)
        b = 0.95;
    else if (b == 2)
        b = 0.98;
    printf("%.2f\n", a * b * n);
    return 0;
}