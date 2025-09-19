#include<stdio.h>

int main() {
    int n, t, sum = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &t);
            if (i == j) sum += t;
        }
    }
    printf("%d\n", sum);
    return 0;
}