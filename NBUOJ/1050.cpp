#include<stdio.h>

int main() {
	int len = 0;
	char ch;
	ch = getchar();
	while (ch != '\n') {
		len++;
		ch = getchar();
	}
	printf("%d\n", len);
	return 0;
}