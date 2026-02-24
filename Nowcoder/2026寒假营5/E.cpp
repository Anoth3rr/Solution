// Problem: 智乃的最大子段和取模
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120565/E
// Memory Limit: 1024 MB
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
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    vector<ll> pre(n + 1);
    for (int i = 1; i <= n; ++i) {
        pre[i] = (pre[i - 1] + a[i - 1]) % p;
    }
    set<PLL> s;
    s.insert({0, 0});
    ll mx = -1;
    int L = 0, R = 0;

    for (int j = 1; j <= n; ++j) {
        ll cur = pre[j];

        if (s.begin() != s.end()) {
            ll val = (cur - s.begin()->fi + p) % p;
            if (val > mx) {
                mx = val;
                L = s.begin()->se;
                R = j - 1;
            }
        }

        auto it = s.upper_bound({cur, INF});
        if (it != s.end()) {
            ll val = (cur - it->fi + p) % p;
            if (val > mx) {
                mx = val;
                L = it->se;
                R = j - 1;
            }
        }

        s.insert({cur, j});
    }

    cout << L << " " << R << " " << mx << endl;
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