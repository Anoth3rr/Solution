#include<stdio.h>

int main() {
    int score;
    scanf("%d", &score);
    if (score >= 60)
        printf("pass\n");
    else
        printf("failure\n");
    return 0;
}