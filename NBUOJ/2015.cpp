#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n;
    cin >> n;
    auto encode = [&](int x, int y, int z) {
        return x * 3600 + y * 60 + z;
    };
    int mx = 0, mn = 1e9;
    string mxloc, mnloc;
    while (n--) {
        string s;
        int a, b, c, x, y, z;
        cin >> s;
        scanf("%d:%d:%d %d:%d:%d", &a, &b, &c, &x, &y, &z);
        int t1 = encode(a, b, c), t2 = encode(x, y, z);
        if (t1 <= mn)
            mn = t1, mnloc = s;
        if (t2 >= mx)
            mx = t2, mxloc = s;
    }
    cout << mnloc << " " << mxloc << endl;
}
int main() {
    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}