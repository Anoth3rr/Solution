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

struct EBCC {
    int n, now, cnt;
    vector<vector<int>> ver;
    vector<int> dfn, low, bel, S;

    EBCC() {}
    EBCC(int n) : n(n), ver(n + 1), low(n + 1) {
        dfn.resize(n + 1, -1);
        bel.resize(n + 1, -1);
        now = cnt = 0;
    }

    void add(int x, int y) {
        ver[x].push_back(y);
        ver[y].push_back(x);
    }

    void tarjan(int x, int fa) {
        dfn[x] = low[x] = now++;
        S.push_back(x);

        for (auto y : ver[x]) {
            if (y == fa) continue;
            if (dfn[y] == -1) {
                tarjan(y, x);
                low[x] = min(low[x], low[y]);
            } else if (bel[y] == -1) {
                low[x] = min(low[x], dfn[y]);
            }
        }

        if (dfn[x] == low[x]) {
            int pre;
            cnt++;
            do {
                pre = S.back();
                bel[pre] = cnt;
                S.pop_back();
            } while (pre != x);
        }
    }

    vector<int> work() {
        for (int i = 1; i <= n; i++) {
            if (dfn[i] == -1) {
                tarjan(i, 0);
            }
        }
        return bel;
    }

    struct Graph {
        int n;
        vector<pair<int, int>> edges;
        vector<int> siz;
        vector<int> cnte;
    };
    Graph compress() {
        Graph g;
        g.n = cnt;
        g.siz.resize(cnt);
        g.cnte.resize(cnt);
        for (int i = 0; i < n; i++) {
            g.siz[bel[i]]++;
            for (auto j : ver[i]) {
                if (bel[i] < bel[j]) {
                    g.edges.emplace_back(bel[i], bel[j]);
                } else if (i < j) {
                    g.cnte[bel[i]]++;
                }
            }
        }
        return g;
    }
};

void init() {

}

void solve() {
    int n, m, V;
    cin >> n >> m >> V;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    EBCC g(n);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        g.add(u, v);
    }

    auto bel = g.work();

    vector<int> vis(n + 1, -1);
    ll ans = 1;
    for (int i = 1; i <= n; ++i) {
        if (vis[i] != -1) continue;
        queue<int> q;
        q.push(i);
        vis[i] = 0;
        bool bip = true;
        vector<int> val;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            val.pb(a[u]);

            for (auto v : g.ver[u]) {
                if (bel[u] != bel[v]) continue;
                if (vis[v] == -1) {
                    vis[v] = vis[u] ^ 1;
                    q.push(v);
                } else if (vis[u] == vis[v]) {
                    bip = false;
                }
            }
        }
        int v = -1;
        for (auto x : val) {
            if (x != -1) {
                if (v != -1 && v != x) {
                    cout << 0 << "\n";
                    return;
                }
                v = x;
            }
        }
        if (bip) {
            if (v == -1) ans = ans * V % MOD;
        } else {
            if (v > 0) {
                cout << 0 << "\n";
                return;
            }
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}