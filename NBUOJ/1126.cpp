#include<stdio.h>
#include<math.h>

bool isNarcissistic(int n) {
    int sum = 0, x = n;
    while (x) {
        sum += pow(x % 10, 3);
        x /= 10;
    }
    if (sum == n)
        return true;
    return false;
}

int main() {
    int n;
    bool flag = true;
    scanf("%d", &n);
    for (int i = 100; i < n; ++i)
        if (isNarcissistic(i))
            printf("%d\n", i), flag = false;
    if (flag)
        printf("No Answer");
    return 0;
}
