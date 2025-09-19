#include<stdio.h>
#include<math.h>

int main() {
    double a, b, c, p;
    scanf("%lf%lf%lf%lf", &a, &b, &c, &p);
    p = (a + b + c) / 2;
    if (a + b > c && a + c > b && b + c > a) {
        printf("%.2f\n", sqrt(p * (p - a) * (p - b) * (p - c)));
    }
    else printf("Error\n");
    return 0;
}