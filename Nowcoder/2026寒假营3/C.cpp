// Problem: Inverted World
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120563/C
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
    int n;
    string s;
    cin >> n >> s;
    auto ssolve = [&](int st) {
        int e0 = 0, e1 = 0;
        for (int i = 0; i < n; ++i) {
            char nxt = ((i & 1) ? (st ? '0' : '1') : (st ? '1' : '0'));
            if (s[i] == nxt)
                continue;
            if (s[i] == '0') {
                if (e1 > 0) {
                    --e1;
                }
                ++e0;
            } else {
                if (e0 > 0) {
                    --e0;
                }
                ++e1;
            }
        }
        return e0 + e1;
    };
    cout << min(ssolve(0), ssolve(1)) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    cin >> t;
    cout << fixed << setprecision(15);
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}