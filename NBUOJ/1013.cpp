#include<stdio.h>
#include<math.h>

int main() {
    double x1, y1, x2, y2, dis = 0;
    scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
    dis = pow(x1 - x2, 2) + pow(y1 - y2, 2);
    printf("%.2f\n", sqrt(dis));
    return 0;
}