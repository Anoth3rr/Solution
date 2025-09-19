#include<stdio.h>
#include<math.h>

int main() {
    double n;
    scanf("%lf", &n);
    if (n == 0) printf("0\n");
    else printf("%d", (int)(n / fabs(n)));
    return 0;
}