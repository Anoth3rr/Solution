// Problem: 智乃的箭头魔术
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120565/G
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// By: Anoth3r

#include <bits/stdc++.h>
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define endl "\n"
using namespace std;

using ll = long long;
using ld = long double;
using ui = unsigned;
using ull = unsigned long long;
using i128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<ll, ll, ll>;

void init() {
}

void solve() {
    string s = "0112233445142015320125410214530214510214102302142025101203201451451522302514203214510021454101002532";
    int c = 0;
    for (auto v : s) {
        if (v == '0')
            c = 3 - c;
        else if (v == '1') {
            if (c == 3)
                c = 1;
            else if (c == 1)
                c = 3;
        } else if (v == '2') {
            if (c == 0)
                c = 1;
            else if (c == 1)
                c = 0;
            else if (c == 3)
                c = 2;
            else if (c == 2)
                c = 3;
        } else if (v == '3') {
            if (c == 0)
                c = 2;
            else if (c == 2)
                c = 0;
        } else if (v == '4') {
            c = (c + 1) % 4;
        } else if (v == '5') {
            c = (c + 3) % 4;
        }
        cout << c;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    cout << fixed << setprecision(15);
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}