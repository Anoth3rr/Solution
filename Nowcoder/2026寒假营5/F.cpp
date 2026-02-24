// Problem: 智乃的算法竞赛群友
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120565/F
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

constexpr ll INF = 2e18;

void init() {
}

void solve() {
    ll n, a, b;
    cin >> n >> a >> b;
    vector<ll> X;
    X.pb(0);
    auto check = [&](ll x) {
        return 0 <= x && x <= n;
    };
    for (int i = -3; i <= 3; ++i) {
        if (check(n / 8 + i))
            X.pb(n / 8 + i);
        if (check(n / 7 + i))
            X.pb(n / 7 + i);
        if (check((n + 1) / 8 + i))
            X.pb((n + 1) / 8 + i);
    }
    for (int i = 0; i <= 6; ++i)
        if (check(i))
            X.pb(i);
    sort(all(X));
    X.erase(unique(all(X)), X.end());

    auto calc = [&](ll x) {
        ll mx = -1;
        if (x <= n / 8) {
            ll t = (n - 6 * x) / 2;
            if (t >= x) {
                mx = t;
            } else {
                if (n - 7 * x >= 0) {
                    mx = max(x - 1, n - 7 * x);
                } else {
                    return -INF;
                }
            }
        } else {
            if (n - 7 * x >= 0) {
                mx = min(x - 1, n - 7 * x);
            } else {
                return -INF;
            }
        }
        if (mx < 0)
            return -INF;
        return a * x + b * mx;
    };

    ll ans = 0;
    bool f = false;
    for (auto x : X) {
        ll val = calc(x);
        if (val == -INF)
            continue;
        if (!f || val > ans) {
            ans = val;
            f = 1;
        }
    }
    if (!f)
        cout << 0 << endl;
    else
        cout << ans << endl;
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