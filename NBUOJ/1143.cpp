#include<bits/stdc++.h>
using namespace std;

void move(char A, char C) {
    printf("%c->%c\n", A, C);
}

void hanoi(int n, char A, char B, char C) {
    if (n == 1) move(A, C);
    else {
        hanoi(n - 1, A, C, B);
        move(A, C);
        hanoi(n - 1, B, A, C);
    }
}

int main() {
    int t;
    cin >> t;
    hanoi(t, 'a', 'b', 'c');
    return 0;
}