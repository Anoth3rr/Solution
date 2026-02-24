// Problem: 01矩阵
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120562/E
// Memory Limit: 2048 MB
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
    cin >> n;

    if (n == 1) {
        cout << "0" << endl;
        return;
    }

    vector<string> g(n, string(n, '0'));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            g[i][j] = '1';
        }
    }
    int l = 0, r = n - 1;
    vector<int> p;
    while (l <= r) {
        p.pb(l++);
        if (l <= r)
            p.pb(r--);
    }

    vector<string> ans(n, string(n, '0'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans[i][j] = g[p[i]][p[j]];
        }
    }
    for (int i = 0; i < n; ++i)
        cout << ans[i] << endl;
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