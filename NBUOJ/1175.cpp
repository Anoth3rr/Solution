#include<stdio.h>
#include<string.h>

int main() {
	char a[110];
	scanf("%s", &a);
	int mx = -1;
	for (int i = 0; i < strlen(a); ++i) {
		mx = a[i] > mx ? a[i] : mx;
	}
	for (int i = 0; i < strlen(a); ++i) {
		printf("%c", a[i]);
		if (a[i] == mx) printf("(max)");
	}
	return 0;
}
