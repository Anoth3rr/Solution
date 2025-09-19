#include<stdio.h>

int main() {
    int a[11], target;
    for (int i = 0; i < 10; ++i)
        scanf("%d", &a[i]);
    scanf("%d", &target);
    int l = 1, r = 10;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (a[mid] == target) {
            printf("%d\n", mid);
            return 0;
        }
        if (a[mid] < target)
            l = mid + 1;
        else
            r = mid - 1;
    }
    printf("not found\n");
    return 0;
}