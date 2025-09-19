#include<stdio.h>

int main() {
    int n, cnt = 0;
    double t, ave = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lf", &t), ave += t;
        if (t < 60) cnt++;
    }
    printf("%.1f\n%d", ave / n, cnt);
    return 0;
}