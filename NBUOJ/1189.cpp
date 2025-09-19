#include<stdio.h>
#include<string.h>

int main() {
	char s[220];
	scanf("%s", &s);
	for (int i = 0; i < strlen(s); ++i) {
		if (s[i] == '1') putchar('0');
		else if (s[i] == '0') putchar('1');
	}
	putchar('\n');
	return 0;
}
