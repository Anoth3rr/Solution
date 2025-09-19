#include<stdio.h>

bool isdigit(char ch) {
    if ('0' <= ch && ch <= '9') return true;
    return false;
}

char rd(double &x) {
    x = 0;
    double t = 0.1;
    int x1 = 0;
    short f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x1 = (x1 << 1) + (x1 << 3) + (ch ^ 48);
        ch = getchar();
    }
    if (ch != '.') {
        x = x1;
        x *= f;
        return ch;
    }
    ch = getchar();
    while (isdigit(ch)) {
        x += t * (ch ^ 48);
        t /= 10;
        ch = getchar();
    }
    x += x1;
    x *= f;
    return ch;
}

int main() {
    double a, b;
    char s;
    bool flag = false;
    s = rd(a);
    rd(b);
    if (s == '+')
        printf("%.2f\n", a + b);
    else if (s == '-')
        printf("%.2f\n", a - b);
    else if (s == '*')
        if (a == 0 || b == 0)
            printf("0.00\n");
        else
            printf("%.2f\n", a * b);
    else if (s == '/')
        if (a == 0)
            printf("0.00\n");
        else
            printf("%.2f\n", a / b);
    return 0;
}