#include<stdio.h>

int main() {
    double x, sum = 0;
    int cnt = 0;
    while (scanf("%lf", &x) != EOF) {
        sum += x;
        cnt++;
    }
    printf("%.2f", sum / cnt);
    return 0;
}