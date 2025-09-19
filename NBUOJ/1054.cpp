#include<stdio.h>
#define maxn 100010

int main() {
    char p, pre;
    pre = getchar();
    p = getchar();
    while (p != '\n') {
        if (p == pre) {
            printf("%c", p);
            return 0;
        }
        pre = p;
        p = getchar();
    }
    printf("No\n");
    return 0;
}