// Problem: C. First or Second
// Contest: Codeforces - Good Bye 2025
// URL: https://codeforces.com/contest/2178/problem/C
// Memory Limit: 256 MB
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
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<ll> pre(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        pre[i] = pre[i - 1] + llabs(a[i]);
    }

    vector<ll> suf(n + 2, 0);
    for (int i = n; i >= 1; i--)
        suf[i] = suf[i + 1] + a[i];

    ll ans = -INF;
    for (int s = 1; s <= n; s++) {
        ll cur;
        if (s == 1) {
            cur = -suf[2];
        } else {
            cur = a[1] + pre[s - 1] - suf[s + 1];
        }
        ans = max(ans, cur);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}