#include<stdio.h>
#include<math.h>

int main() {
    double x;
    scanf("%lf", &x);
    if (x >= 0) printf("%.2f\n", sqrt(x));
    else printf("%.2f\n", (x + 1) * (x + 1) + 2 * x + 1 / x);
    return 0;
}