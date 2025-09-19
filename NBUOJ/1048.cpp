#include<stdio.h>

int main() {
    double n;
    scanf("%lf", &n);
    n -= 3500;
    if (n <= 1500) printf("%.2f\n", n * 0.03);
    else if (1500 < n && n <= 4500) printf("%.2f\n", n * 0.1 - 105);
    else if (4500 < n && n <= 9000) printf("%.2f\n", n * 0.2 - 555);
    else if (9000 < n && n <= 35000) printf("%.2f\n", n * 0.25 - 1005);
    else if (35000 < n && n <= 55000) printf("%.2f\n", n * 0.3 - 2755);
    else if (55000 < n && n <= 80000) printf("%.2f\n", n * 0.35 - 5505);
    else printf("tax=%.2f\n", n * 0.45 - 13505);
    return 0;
}