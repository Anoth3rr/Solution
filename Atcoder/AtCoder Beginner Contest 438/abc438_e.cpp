// Problem: E - Heavy Buckets
// Contest: AtCoder - AtCoder Beginner Contest 438
// URL: https://atcoder.jp/contests/abc438/tasks/abc438_e
// Memory Limit: 1024 MB
// Time Limit: 3000 ms
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
constexpr int K = 31;

void init() {}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> up(K, vector<int>(n + 1));
    vector<vector<ll>> sum(K, vector<ll>(n + 1));

    for (int i = 1; i <= n; ++i) {
        up[0][i] = a[i];
        sum[0][i] = i;
    }
    for (int k = 0; k + 1 < K; ++k) {
        for (int i = 1; i <= n; ++i) {
            int mid = up[k][i];
            up[k + 1][i] = up[k][mid];
            sum[k + 1][i] = sum[k][i] + sum[k][mid];
        }
    }

    while (q--) {
        ll t;
        int b;
        cin >> t >> b;
        ll ans = 0;
        int cur = b;
        for (int i = 0; i < K; ++i) {
            if ((t >> i) & 1ll) {
                ans += sum[i][cur];
                cur = up[i][cur];
            }
        }
        cout << ans << endl;
    }
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