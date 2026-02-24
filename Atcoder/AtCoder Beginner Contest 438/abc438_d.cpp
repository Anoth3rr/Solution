// Problem: D - Tail of Snake
// Contest: AtCoder - AtCoder Beginner Contest 438
// URL: https://atcoder.jp/contests/abc438/tasks/abc438_d
// Memory Limit: 1024 MB
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

    vector<ll> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        cin >> c[i];

    vector<ll> sa(n + 1), sb(n + 1), sc(n + 1);
    for (int i = 1; i <= n; i++) {
        sa[i] = sa[i - 1] + a[i];
        sb[i] = sb[i - 1] + b[i];
        sc[i] = sc[i - 1] + c[i];
    }

    ll S = sa[1] - sb[1];
    ll ans = -INF;

    for (int y = 2; y <= n - 1; y++) {
        ans = max(ans, S + (sb[y] - sc[y]));
        S = max(S, sa[y] - sb[y]);
    }

    ans += sc[n];
    cout << ans << endl;
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