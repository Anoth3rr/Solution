#include<stdio.h>

int main() {
    int cnt = 0;
    double t, ave = 0;
    scanf("%lf", &t);
    while (t >= 0)
        ave += t, cnt++, scanf("%lf", &t);
    printf("%.1f\n", ave / cnt);
    return 0;
}