#include<stdio.h>

int main() {
    double t, sum = 0;
    scanf("%lf", &t);
    while (t != 0)
        sum += t, scanf("%lf", &t);
    printf("%.2f\n", sum);
    return 0;
}