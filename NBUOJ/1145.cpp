#include<stdio.h>
#include<string.h>

int main() {
    char a[110];
    scanf("%s", &a);
    int len = strlen(a);
    for (int i = 0; i < len / 2; ++i)
        if (a[i] != a[len - i - 1]) {
            printf("No\n");
            return 0;
        }
    printf("Yes\n");
    return 0;
}