#include<bits/stdc++.h>
using namespace std;
int main() {
    unsigned long long m, n, ans = 1;
    cin >> m >> n;
    n = min(n, m - n);
    for (int i = 0; i < n; ++i) {
        ans *= m - i;
    }
    for (int i = 1; i <= n; ++i) {
        ans /= i;
    }
    cout << ans << endl;
    return 0;
}