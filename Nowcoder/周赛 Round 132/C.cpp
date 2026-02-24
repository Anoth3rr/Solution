// Problem: 邻合
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/128672/C
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

constexpr int inf = 1e9 + 7;

void init() {
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    int dp0 = 0, dp1 = -inf;
    if (a[0] > 1)
        dp1 = 1;
    for (int i = 1; i < n; ++i) {
        int ndp0 = max(dp0, dp1), ndp1 = -inf;
        if (a[i] > 1) {
            ndp1 = dp0 + 1;
            if (dp1 > -inf && __gcd(a[i], a[i - 1]) > 1)
                ndp1 = max(ndp1, dp1 + 1);
        }
        dp0 = ndp0, dp1 = ndp1;
    }
    cout << n - max(dp0, dp1) << endl;
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