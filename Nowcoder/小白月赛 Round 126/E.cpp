// Problem: 小红做梦
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126282/E
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
    ll x, a, b, c;
    cin >> x >> a >> b >> c;

    ll ans = INF, cur = x;

    auto ssolve = [&](ll X) {
        ll l = 1005, r = 1011;
        while (1) {
            if (l <= X && X < r) {
                return 0ll;
            }

            if (X < l) {
                ll n = (l - X + c - 1) / c;
                if (n * c + X < r) {
                    return n;
                }
            }
            l *= 10, r *= 10;
        }
    };

    for (int i = 0; i <= 17; ++i) {
        ans = min(ans, a * i + ssolve(cur) * b);
        cur /= 10;
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