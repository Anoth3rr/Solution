//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef __int128 i128;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef tuple<ll, ll, ll> TLLL;
typedef __gnu_pbds::tree<PLL, __gnu_pbds::null_type, less<PLL>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;
// typedef __gnu_pbds::tree<ll, __gnu_pbds::null_type, less<ll>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ld PI = acos(-1.0);
constexpr ld eps = 1e-10;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

void init() {

}

void solve() {
    ll n, y;
    cin >> n >> y;
    vector<int> c(n);
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        if (c[i] > mx) mx = c[i];
    }

    vector<int> freq(mx + 1, 0);
    for (int v : c) freq[v]++;

    vector<int> pre(mx + 1, 0);
    for (int i = 1; i <= mx; i++) pre[i] = pre[i - 1] + freq[i];

    ll ans = -INF;
    for (int i = 2; i <= mx + 1; ++i) {
        ll tot = 0;
        ll re = 0;
        int vm = (mx + i - 1) / i;
        for (int j = 1; j <= vm; ++j) {
            int L = (j - 1) * i + 1;
            int R = min(j * i, mx);
            if (L > R) continue;
            int cnt = pre[R] - pre[L - 1];
            if (cnt == 0) continue;
            tot += (ll)j * (ll)cnt;
            if (j <= mx) re += min(cnt, freq[j]);
        }
        ll t = tot - (n - re) * y;
        if (t > ans) ans = t;
    }
    cout << ans << "\n";
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