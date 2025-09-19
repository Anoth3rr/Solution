#include<stdio.h>
#include<math.h>

int main() {
    double a, b, c;
    scanf("%lf%lf%lf", &a, &b, &c);
    double delta = b * b - 4 * a * c;
    double x1 = (-b + sqrt(delta)) / 2 / a, x2 = (-b - sqrt(delta)) / 2 / a;
    if (delta == 0)
        printf("%.2f\n", x1);
    else
        printf("%.2f %.2f\n", x1 > x2 ? x1 : x2, x1 > x2 ? x2 : x1);
    return 0;
}