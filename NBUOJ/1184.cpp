#include<stdio.h>
#include<string.h>
#define min(a,b) a<b?a:b

int main() {
	char a[1010], b[1010];
	scanf("%s%s", &a, &b);
	for (int i = 0; i < min(strlen(a), strlen(b)); ++i) {
		if (a[i] < b[i]) {
			printf("%s\n%s", a, b);
			return 0;
		}
		else if (a[i] > b[i]) {
			printf("%s\n%s", b, a);
			return 0;
		}
	}
	if (strlen(a) > strlen(b))
		printf("%s\n%s", b, a);
	else
		printf("%s\n%s", a, b);
	return 0;
}
