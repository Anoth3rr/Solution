// Problem: F - Sum of Mex
// Contest: AtCoder - AtCoder Beginner Contest 438
// URL: https://atcoder.jp/contests/abc438/tasks/abc438_f
// Memory Limit: 1024 MB
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

struct LCA {
    int n, LOG;
    vector<vector<int>> up;
    vector<int> dep, parent;
    vector<vector<int>> adj;
    LCA(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        LOG = 1;
        while ((1 << LOG) <= max(1, n))
            ++LOG;
        up.assign(LOG, vector<int>(n + 1, 0));
        dep.assign(n + 1, 0);
        parent.assign(n + 1, 0);
        adj.assign(n + 1, {});
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void build(int root = 1) {
        vector<int> order;
        order.reserve(n);
        order.push_back(root);
        parent[root] = 0;
        dep[root] = 0;
        for (size_t i = 0; i < order.size(); ++i) {
            int u = order[i];
            for (int v : adj[u])
                if (v != parent[u]) {
                    parent[v] = u;
                    dep[v] = dep[u] + 1;
                    order.push_back(v);
                }
        }
        for (int v = 1; v <= n; ++v)
            up[0][v] = parent[v] == 0 ? v : parent[v];
        for (int k = 1; k < LOG; ++k) {
            for (int v = 1; v <= n; ++v)
                up[k][v] = up[k - 1][up[k - 1][v]];
        }
    }
    int kth_up(int u, int k) {
        int cur = u;
        for (int b = 0; b < LOG; ++b)
            if ((k >> b) & 1)
                cur = up[b][cur];
        return cur;
    }
    int lca(int x, int y) {
        if (dep[x] < dep[y])
            swap(x, y);
        int diff = dep[x] - dep[y];
        x = kth_up(x, diff);
        if (x == y)
            return x;
        for (int k = LOG - 1; k >= 0; --k) {
            if (up[k][x] != up[k][y]) {
                x = up[k][x];
                y = up[k][y];
            }
        }
        return up[0][x];
    }
    int dist(int x, int y) {
        int c = lca(x, y);
        return dep[x] + dep[y] - 2 * dep[c];
    }
    int kth_on_path(int u, int v, int k) {
        int c = lca(u, v);
        int du = dep[u] - dep[c];
        if (k <= du) {
            return kth_up(u, k);
        } else {
            int rem = k - du;
            int dv = dep[v] - dep[c];
            int steps_up = dv - rem;
            return kth_up(v, steps_up);
        }
    }
};

void init() {}

void solve() {
    int n;
    cin >> n;
    LCA lca(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        lca.add_edge(u + 1, v + 1);
    }
    lca.build(1);

    vector<int> p = lca.parent, sub(n + 1);
    vector<int> ord = {1};
    for (int i = 0; i < (int)ord.size(); i++) {
        int u = ord[i];
        for (int v : lca.adj[u])
            if (v != p[u])
                ord.push_back(v);
    }
    for (int i = n - 1; i >= 0; i--) {
        int u = ord[i];
        sub[u] = 1;
        for (int v : lca.adj[u])
            if (v != p[u])
                sub[u] += sub[v];
    }

    auto comp = [&](int a, int b) {
        if (p[b] == a)
            return (ll)n - sub[b];
        if (p[a] == b)
            return (ll)sub[a];
        return (ll)sub[a];
    };

    ll ans = 0;
    int L = 1, R = 1;
    ll m = 1;

    for (int t = 1; t <= n; t++) {
        if (m == 1) {
            int v = L;
            ll s = 0;
            for (int to : lca.adj[v]) {
                ll x = (p[to] == v ? sub[to] : n - sub[v]);
                s += x * (x - 1) / 2;
            }
            ans += (ll)n * (n - 1) / 2 - s + 1;
        } else {
            int d = lca.dist(L, R);
            if (m == d + 1) {
                int nl = lca.kth_on_path(L, R, 1);
                int nr = lca.kth_on_path(R, L, 1);
                ans += comp(L, nl) * comp(R, nr);
            }
        }
        if (t == n)
            break;
        int u = t + 1;
        int dLR = lca.dist(L, R);
        int dLu = lca.dist(L, u);
        int dRu = lca.dist(R, u);
        int nL = L, nR = R;
        if (dLu >= dRu && dLu >= dLR) {
            nL = L;
            nR = u;
        } else if (dRu >= dLu && dRu >= dLR) {
            nL = R;
            nR = u;
        }
        int add = (dLu + dRu - dLR) / 2;
        L = nL;
        R = nR;
        m += add;
    }

    cout << ans << "\n";
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