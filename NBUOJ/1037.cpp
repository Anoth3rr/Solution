#include<stdio.h>
#include<math.h>

int main() {
    double n, m;
    scanf("%lf%lf", &n, &m);
    printf("%.2f\n", sqrt(n * n + m * m));
    return 0;
}