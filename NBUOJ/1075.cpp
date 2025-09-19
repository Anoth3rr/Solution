#include<stdio.h>

int a1[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
int a2[13] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n % 4 == 0 && n % 100 != 0 || n % 400 == 0) {
        for (int i = 1; i < 12; ++i) {
            if (a2[i - 1] < m && m <= a2[i]) {
                printf("%d-%d-%d", n, i, m - a2[i - 1]);
                return 0;
            }
        }
    }
    else {
        for (int i = 1; i < 12; ++i) {
            if (a1[i - 1] < m && m <= a1[i]) {
                printf("%d-%d-%d", n, i, m - a1[i - 1]);
                return 0;
            }
        }
    }
    return 0;
}