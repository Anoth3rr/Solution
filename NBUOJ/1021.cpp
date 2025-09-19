#include<stdio.h>

int main() {
    double x, y;
    scanf("%lf%lf", &x, &y);
    printf("%.1f\n", (90 - x * 0.1 - y * 0.3) / 0.6);
    return 0;
}