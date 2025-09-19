#include<stdio.h>

int main() {
    int a[1000];
    int cur = 0;
    while (scanf("%d", &a[cur]) != EOF)
        cur++;
    for (int i = 0; i < cur - 1; ++i)
        if (a[i] == a[cur - 1]) {
            printf("%d", i);
            return 0;
        }
    printf("not found");
    return 0;
}