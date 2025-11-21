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
    int n, m;
    cin >> n >> m;
    vector<vector<PLL>> g(2 * n + 2);
    vector<array<ll, 3>> edges;
    vector<ll> mnw(n + 1, inf);
    for (int i = 0; i < m; ++i) {
        ll u, v, w;
        cin >> u >> v >> w;
        edges.pb({u, v, w});
        mnw[u] = min(mnw[u], w);
        mnw[v] = min(mnw[v], w);
    }


    for (auto [u, v, w] : edges) {
        if (mnw[u] != inf) g[u].eb(v, min(mnw[u] * 2, w));
        else g[u].eb(v, w);
        if (mnw[v] != inf) g[v].eb(u, min(mnw[v] * 2, w));
        else g[v].eb(u, w);
    }

    vector<ll> dist(2 * n + 2, INF);
    priority_queue<PLL, vector<PLL>, greater<PLL>> pq;
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) {
            w += d;
            if (w < dist[v]) {
                dist[v] = w;
                pq.push({w, v});
            }
        }
    }

    ll ans = dist[n];
    if (ans >= INF) cout << -1 << "\n";
    else cout << ans << "\n";
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