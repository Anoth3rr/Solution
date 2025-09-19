#include<stdio.h>

void trans(int t) {
    if (t < 8) {
        printf("%d ", t);
        return;
    }
    trans(t / 8);
    printf("%d ", t % 8);
}

int main() {
    int t;
    scanf("%d", &t);
    trans(t);
    return 0;
}