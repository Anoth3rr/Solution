#include<stdio.h>
#include<math.h>

int main() {
    double x;
    scanf("%lf", &x);
    if (x >= 0) printf("%.2f\n", x * x - 2);
    else printf("%.2f\n", sqrt(5 - x));
    return 0;
}