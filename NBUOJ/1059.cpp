#include<stdio.h>

int main() {
    int score;
    scanf("%d", &score);
    if (80 <= score && score <= 100)
        printf("A\n");
    else if (60 <= score && score <= 79)
        printf("B\n");
    else
        printf("C\n");
    return 0;
}