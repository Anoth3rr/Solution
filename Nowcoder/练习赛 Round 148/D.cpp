// Problem: 小R的gcd
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/119900/D
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
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    vector<vector<int>> mp(1001);
    vector<PII> pr;
    for (int i = 0; i < n; ++i) {
        if (a[i] % b[i] != 0) continue;
        int x = a[i] / b[i];
        mp[b[i]].pb(x);
        pr.eb(b[i], x);
    }
    vector<vector<int>> cnt(1001, vector<int>(1001));
    for (int i = 1; i <= 1000; ++i) {
        if (mp[i].empty()) continue;
        for (ll x : mp[i]) {
            int lim = min((int)floor(sqrt(1.0 * x)), 1000);
            for (int d = 1; d <= lim; ++d) {
                if (x % d == 0) {
                    cnt[i][d]++;
                    int o = x / d;
                    if (o != d && o <= 1000) cnt[i][o]++;
                }
            }
        }
    }
    ll tot = 0;
    for (auto [u, v] : pr) {
        int c = 0, lim = min((int)floor(sqrt(1.0 * v)), 1000);
        for (ll d = 1; d <= lim; ++d) {
            if (v % d == 0) {
                c += cnt[d][u];
                int o = v / d;
                if (o != d && o <= 1000) {
                    c += cnt[o][u];
                }
            }
        }
        c -= (v % u == 0);
        tot += c;
    }

    cout << (tot / 2) << endl;
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