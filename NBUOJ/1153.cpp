#include<bits/stdc++.h>
using namespace std;
int main() {
    int a[13];
    for (int i = 1; i <= 11; ++i)
        cin >> a[i];
    sort(a + 1, a + 12);
    for (int i = 1; i <= 11; ++i)
        cout << a[i] << " ";
    return 0;
}