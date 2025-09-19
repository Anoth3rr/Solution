#include<stdio.h>

int main() {
    double x, y;
    scanf("%lf%lf", &x, &y);
    printf("%.2f\n", x * 0.538 + y * 0.03);
    return 0;
}