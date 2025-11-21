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

vector<bool> flg;

struct DSU {
    vector<int> f, siz;

    DSU() {}
    DSU(int n) {
        init(n);
    }

    void init(int n) {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }

    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool merge(int x, int y, ll& c) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) swap(x, y);
        if (flg[x] && !flg[y]) {
            c += siz[y];
        } else if (!flg[x] && flg[y]) {
            c += siz[x];
        }

        siz[x] += siz[y];
        f[y] = x;
        flg[x] = flg[x] || flg[y];
        return true;
    }

    int size(int x) {
        return siz[find(x)];
    }
};

struct Edge {
    int u, v, val;

    bool operator<(const Edge& o) const {
        return val < o.val;
    }
};

struct Query {
    int x, idx;

    bool operator<(const Query& o) const {
        return x < o.x;
    }
};

int X[] = { -1, 1, 0, 0}, Y[] = {0, 0, -1, 1};

void init() {

}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    auto encode = [&](int x, int y) {
        return x * m + y;
    };

    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> g[i][j];
        }
    }

    vector<Edge> edge;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int u = encode(i, j);
            for (int k = 0; k < 4; ++k) {
                int nx = i + X[k];
                int ny = j + Y[k];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    if (nx > i || (nx == i && ny > j)) {
                        int v = encode(nx, ny);
                        edge.pb({u, v, max(g[i][j], g[nx][ny])});
                    }
                }
            }
        }
    }

    sort(all(edge));

    vector<Query> qs(q);
    for (int i = 0; i < q; ++i) {
        cin >> qs[i].x;
        qs[i].idx = i;
    }

    sort(all(qs));
    vector<ll> ans(q);

    DSU dsu(n * m);
    flg.assign(n * m, 0);

    ll cnt = 0;

    int ptr = 0;
    for (int i = 0; i < q; ++i) {
        ll cur = qs[i].x;
        while (ptr < edge.size() && edge[ptr].val <= cur) {
            dsu.merge(edge[ptr].u, edge[ptr].v, cnt);
            ptr++;
        }

        for (int j = 0; j < m; ++j) {
            if (g[0][j] <= cur) {
                int rt = dsu.find(encode(0, j));
                if (!flg[rt]) {
                    cnt += dsu.siz[rt];
                    flg[rt] = true;
                }
            }
        }
        ans[qs[i].idx] = cnt;
    }

    for (int i = 0; i < q; ++i) cout << ans[i] << "\n";
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