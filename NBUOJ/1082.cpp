#include<stdio.h>

int d[4][2] = {
    {2, 2},
    {2, -2},
    { -2, 2},
    { -2, -2}
};

int main() {
    double x, y;
    bool flag = false;
    scanf("%lf&lf", &x, &y);
    for (int i = 0; i <= 3; ++i) {
        double dis = (x - d[i][0]) * (x - d[i][0]) + (y - d[i][1]) * (y - d[i][1]);
        if (dis <= 1) {
            flag = true;
            break;
        }
    }
    if (flag)
        printf("50\n");
    else
        printf("0\n");
    return 0;
}