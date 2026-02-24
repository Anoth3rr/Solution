// Problem: 「SFCOI-4」序列与变换
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120679/B
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
    ll n, m;
    cin >> n >> m;

    int s = (m % 4 == 1 || m % 4 == 2) ? 1 : 0;
    bool f = (m >= 1e9);
    ll S = f ? 0 : m * (m + 1) / 2;
    int c0 = 0, c1 = 0;

    for (int i = 0; i < n; ++i) {
        ll a;
        cin >> a;

        if (f || a <= S) {
            if (a % 2 == s) {
                c0++;
            } else {
                c1++;
            }
        } else {
            int res = a - S;
            if (res == 0) {
                c0++;
            } else if (res == 1) {
                c1++;
            }
        }
    }
    cout << c0 << " " << c1 << endl;
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