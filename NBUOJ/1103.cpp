#include<stdio.h>

int D[] = {1, -1};

int main() {
    int a = 123, b = 45, c = 67, d = 8, e = 9, n;
    scanf("%d", &n);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                for (int l = 0; l < 2; ++l)
                    if (a + D[i]*b + D[j]*c + D[k]*d + D[l]*e == n) {
                        printf("%d%c%d%c%d%c%d%c%d=%d\n", a, D[i] == 1 ? '+' : '-', b, D[j] == 1 ? '+' : '-', c, D[k] == 1 ? '+' : '-', d, D[l] == 1 ? '+' : '-', e, n);
                        return 0;
                    }
    printf("impossible\n");
    return 0;
}