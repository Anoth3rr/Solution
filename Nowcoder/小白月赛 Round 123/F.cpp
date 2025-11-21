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

template<class Int>
struct DSU {
    vector<int> f, siz;
    vector<Int> w;

    DSU(int n_) {
        init(n_);
    }

    void init(int n) {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
        w.assign(n + 1, 0);
    }

    int find(int x) {
        if (f[x] == x) return x;
        int fx = find(f[x]);
        w[x] += w[f[x]];
        return f[x] = fx;
    }

    Int get(int x) {
        find(x);
        return w[x];
    }

    bool merge(int x, int y, Int diff) {
        int fx = find(x), fy = find(y);
        if (fx == fy) {
            return (w[x] - w[y] == diff);
        }
        if (siz[fx] < siz[fy]) {
            f[fx] = fy;
            w[fx] = diff - w[x] + w[y];
            siz[fy] += siz[fx];
        } else {
            f[fy] = fx;
            w[fy] = w[x] - w[y] - diff;
            siz[fx] += siz[fy];
        }
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

void init() {

}

void solve() {
    int n, q;
    cin >> n >> q;
    DSU<ll> g(n);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, v;
            ll k;
            cin >> u >> v >> k;
            bool ok = g.merge(u, v, k);
            if (ok) cout << "OK" << "\n";
            else cout << "CONTRADICTION" << "\n";
        } else if (op == 2) {
            int u;
            ll k;
            cin >> u >> k;
            bool ok = g.merge(u, 0, k);
            if (ok) cout << "OK" << "\n";
            else cout << "CONTRADICTION" << "\n";
        } else if (op == 3) {
            int u, v;
            cin >> u >> v;
            if (g.same(u, v)) {
                cout << g.w[u] - g.w[v] << "\n";
            } else {
                cout << "UNKNOWN" << "\n";
            }
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