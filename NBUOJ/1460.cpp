#include <bits/stdc++.h>
using namespace std;
void solve() {
    int x;
    cin >> x;
    int ptr = 1;
    assert(x != 6174);
    while (x != 6174) {
        cout << "Step " << ptr << ":";
        string s1 = to_string(x), s2 = s1;
        sort(s1.rbegin(), s1.rend());
        sort(s2.begin(), s2.end());
        x = stoi(s1);
        int y = stoi(s2);
        cout << x << "-" << y << "=" << (x - y) << endl;
        ptr++;
        x -= y;
    }
}
int main() {
    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case " << _ << endl;
        solve();
    }

    return 0;
}