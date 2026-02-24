// Problem: 小红的左看右看构造
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126611/D
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// By: Anoth3r

#include <bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define endl "\n"
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using i128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<ll, ll, ll>;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ld eps = 1e-10;

void init() {}

void solve() {
    int x, y, n;
    cin >> x >> y >> n;
    int c, d;
    vector<int> ans(n);
    for (int i = 0, t; i < x; ++i) {
        cin >> t;
        if (i < x - 1)
            ans[i] = t;
        else
            c = t;
    }
    for (int i = 0, t; i < y; ++i) {
        cin >> t;
        if (i < y - 1)
            ans[n - 1 - i] = t;
        else
            d = t;
    }
    if (c != d) {
        cout << -1 << endl;
        return;
    }
    if (x + y - 1 > n) {
        cout << -1 << endl;
        return;
    }
    ans[x - 1] = c;
    int i = x;
    while (!ans[i])
        ans[i++] = 1;
    for (int i = 0; i < n; ++i)
        cout << ans[i] << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}