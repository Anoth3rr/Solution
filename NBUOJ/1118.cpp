#include<stdio.h>

int main() {
    int n;
    double t = 100, sum = 100;
    scanf("%d", &n);
    n--;
    while (n--) {
        sum += t;
        t /= 2;
    }
    printf("%.6f %.6f\n", sum, t / 2);
    return 0;
}