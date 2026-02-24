// Problem: D. Xmas or Hysteria
// Contest: Codeforces - Good Bye 2025
// URL: https://codeforces.com/contest/2178/problem/D
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

struct node {
    ll val;
    int id;
};

void init() {}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<node> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].val;
        a[i].id = i + 1;
    }
    sort(all(a), [&](node a, node b) { return a.val < b.val; });
    if (m == 0) {
        if (n < 2) {
            cout << "-1" << endl;
            return;
        }

        node A = a[n - 1], B = a[n - 2];

        vector<node> b;
        for (int i = 0; i < n - 2; ++i) {
            b.pb(a[i]);
        }

        ll mn = A.val - B.val, mx = A.val - 1;

        vector<node> S, U;
        ll cur = 0;

        for (int i = b.size() - 1; i >= 0; --i) {
            if (cur + b[i].val <= mx) {
                S.pb(b[i]);
                cur += b[i].val;
            } else {
                U.pb(b[i]);
            }
        }

        if (cur < mn) {
            cout << "-1" << endl;
            return;
        }

        vector<PII> ops;

        if (!U.empty()) {
            sort(all(U), [&](node a, node b) { return a.val < b.val; });

            for (int i = 0; i < U.size() - 1; ++i) {
                ops.pb({U[i].id, U[i + 1].id});
            }
            ops.pb({U.back().id, B.id});
        }

        for (auto s : S) {
            ops.pb({s.id, A.id});
        }

        ops.pb({A.id, B.id});

        cout << ops.size() << endl;
        for (auto [u, v] : ops) {
            cout << u << " " << v << endl;
        }
    } else {
        if (n < 2 * m) {
            cout << "-1" << endl;
            return;
        }

        int K = n - 2 * m;

        vector<PII> ops;

        for (int i = 0; i < K; ++i) {
            ops.pb({a[i].id, a[i + 1].id});
        }

        int st1 = n - m, st2 = n - 2 * m;

        for (int i = 0; i < m; ++i) {
            ops.pb({a[st1 + i].id, a[st2 + i].id});
        }

        cout << ops.size() << endl;
        for (auto [u, v] : ops) {
            cout << u << " " << v << endl;
        }
    }
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