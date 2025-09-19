#include<stdio.h>

int main() {
	char s[110];
	char *p = s;
	int cnt = 0;
	while (((*p) = getchar()) != '\n') cnt++, p++;
	(*p) = '\0';
	printf("%d %s", cnt, s);
	return 0;
}
