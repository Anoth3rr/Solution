//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(),a.rend()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef __int128 lll;
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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<PII> vp;
    for (int i = 0; i < n; ++i) cin >> a[i], vp.eb(a[i], i);
    int m = (n + k - 1) / k;
    sort(all(vp), [&](auto a, auto b) {
        if (a.fi != b.fi) return a.fi > b.fi;
        return a.se < b.se;
    });
    ll ans = 0;
    vector<bool> vis(n);
    for (int i = 0; i < m; ++i) {
        ans += vp[i].fi;
        vis[vp[i].se] = 1;
    }
    cout << ans << "\n";
    vector<int> stk;
    int cur = 0;
    for (int i = 1; i <= n; ++i) {
        bool f = i % k == 1;
        if (f) {
            while (cur < n && !( !stk.empty() && vis[stk.back()] )) {
                if (cur > n) break;
                stk.pb(cur++);
            }
            if (!stk.empty() && vis[stk.back()]) {
                int idx = stk.back(); stk.pop_back();
                vis[idx] = 0;
                cout << a[idx] << " ";
            }
        } else {
            while (cur < n && !(!stk.empty() && !vis[stk.back()] )) {
                if (cur > n) break;
                stk.pb(cur++);
            }
            if (!stk.empty() && !vis[stk.back()]) {
                int idx = stk.back(); stk.pop_back();
                cout << a[idx] << " ";
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}