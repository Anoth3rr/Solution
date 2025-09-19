#include<stdio.h>
#define PI 3.14

int main() {
	double x;
	char c;
	scanf("%lf%c", &x, &c);
	if (c == 's') printf("%.2f", x * x);
	else printf("%.2f", x * x * PI);
	return 0;
}
