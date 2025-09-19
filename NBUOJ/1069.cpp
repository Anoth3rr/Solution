#include<stdio.h>

int main() {
    double v;
    scanf("%lf", &v);
    if (7.91 <= v && v < 11.19)
        printf("1\n");
    else if (11.19 < v && v < 16.67)
        printf("2\n");
    else if (v >= 16.67)
        printf("3\n");
    return 0;
}