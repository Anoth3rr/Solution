#include<stdio.h>
#include<string.h>

int main() {
	int d = 0, x = 0, s = 0;
	char ss[1000010];
	for (int i = 0; i < 3; ++i) {
		fgets(ss, sizeof(ss), stdin);
		for (int j = 0; j < strlen(ss); ++j) {
			if ('A' <= ss[j] && ss[j] <= 'Z') d++;
			if ('a' <= ss[j] && ss[j] <= 'z') x++;
			if ('0' <= ss[j] && ss[j] <= '9') s++;
		}
	}
	printf("%d %d %d\n", d, x, s);
	return 0;
}
