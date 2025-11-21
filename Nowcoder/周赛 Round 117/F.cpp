//Anoth3r
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
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }

    vector<int> fa(n + 1, -1);
    vector<int> order;
    order.pb(1);
    fa[1] = -1;
    for (int i = 0; i < order.size(); ++i) {
        int u = order[i];
        for (int v : g[u]) {
            if (v == fa[u]) continue;
            fa[v] = u;
            order.pb(v);
        }
    }

    vector<array<int, 10>> dp1(n + 1), dp2(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 9; ++j) {
            dp1[i][j] = 0;
            dp2[i][j] = 0;
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        dp1[u][0] = 1;
        for (int v : g[u]) {
            if (v == fa[u]) continue;
            for (int j = 1; j <= 9; ++j) {
                dp1[u][j] += dp1[v][j - 1];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        int u = order[i];
        array<int, 10> tot;
        for (int j = 0; j <= 9; ++j) tot[j] = dp1[u][j] + dp2[u][j];

        for (int v : g[u]) {
            if (v == fa[u]) continue;
            dp2[v][0] = 0;
            for (int j = 1; j <= 9; ++j) {
                int t = tot[j - 1];
                if (j - 2 >= 0) t -= dp1[v][j - 2];
                dp2[v][j] = t;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << dp1[i][9] + dp2[i][9] << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    init();

    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    return 0;
}
