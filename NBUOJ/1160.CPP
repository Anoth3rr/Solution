#include<stdio.h>

int main() {
    int t;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 4; ++j) {
            scanf("%d", &t);
            printf("%d ", t + 1);
        }
        printf("\n");
    }
    return 0;
}