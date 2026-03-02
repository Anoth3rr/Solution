#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    cin >> s;
    char p = '@';
    int ans = 0, cnt = 0;
    for (auto v : s) {
        if (cnt == 5) {
            ans++, cnt = 1;
        } else if (v == p) {
            cnt++;
        } else {
            ans += (cnt > 0);
            cnt = 1;
        }
        p = v;
    }
    ans += (cnt > 0);
    cout << ans << endl;
    return 0;
}