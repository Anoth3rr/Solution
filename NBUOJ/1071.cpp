#include<stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        if (i % 35 == 0) printf("%d ", i);
    }
    printf("\n");
    return 0;
}