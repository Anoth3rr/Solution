// Problem: 小红开机厅
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126282/F
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
    int n;
    cin >> n;

    ll xa, ya, xb, yb;
    cin >> xa >> ya >> xb >> yb;

    ll X = llabs(xa - xb), Y = llabs(ya - yb);
    ll L = X + Y;

    int ch = 0;
    if (xa == xb && ya == yb) {
        ch = 1;
    } else {
        ch = 2;
    }

    vector<ll> qs(n);
    map<ll, int> cnt;

    for (int i = 0; i < n; ++i) {
        ll x, y;
        cin >> x >> y;
        ll dist = llabs(x - xa) + llabs(y - ya) + llabs(x - xb) + llabs(y - yb);
        qs[i] = dist;
        cnt[dist]++;
    }

    for (int i = 0; i < n; ++i) {
        ll K = qs[i];
        ll tot = 0;

        if (K == L) {
            tot = (X + 1) * (Y + 1);
        } else {
            tot = 2 * K;
        }

        ll ex = 0;

        if (K == L) {
            ex += ch;
        }

        if (cnt.count(K)) {
            ex += cnt[K];
        }

        cout << (tot - ex) << " ";
    }
    cout << endl;
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