#include<stdio.h>

int main() {
    double a, b, c, d;
    scanf("%lf%lf%lf%lf", &a, &c, &d, &b);
    if (a > b)
        printf("solid blue and white candle");
    else if (a < b)
        printf("hollow red candle");
    else
        printf("cross red candle");
    if (c > a && c > b)
        printf(",upper shadow");
    if (d < a && d < b)
        printf(",lower shadow");
    printf("\n");
    return 0;
}