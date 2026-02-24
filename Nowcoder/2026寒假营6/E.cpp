// Problem: 小L的空投
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120566/E
// Memory Limit: 512 MB
// Time Limit: 6000 ms
// By: Anoth3r

#include <bits/stdc++.h>
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define endl "\n"
using namespace std;

using ll = long long;
using ld = long double;
using ui = unsigned;
using ull = unsigned long long;
using i128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<ll, ll, ll>;

struct DSU {
    vector<int> f, siz;

    DSU() {}
    DSU(int n) {
        init(n);
    }

    void init(int n) {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
    }

    int find(int x) {
        return f[x] == x ? x : f[x] = find(f[x]);
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y)
            return;
        f[y] = x;
        siz[x] += siz[y];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return siz[find(x)];
    }
};

void init() {
}

void solve() {
    int n, m, x, d;
    cin >> n >> m >> x >> d;

    vector<int> h(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
    }

    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }

    vector<int> H(x + 1);
    for (int i = 1; i <= x; ++i) {
        cin >> H[i];
    }

    vector<int> p(n);
    iota(all(p), 1);
    sort(all(p), [&](int a, int b) {
        return h[a] > h[b];
    });

    DSU dsu(n);
    vector<bool> f(n + 1);
    int cur = 0;
    vector<int> ans(x + 1);

    int ptr = 0;

    for (int i = x; i >= 1; --i) {
        int level = H[i];

        while (ptr < n && h[p[ptr]] > level) {
            int u = p[ptr];
            f[u] = 1;

            if (1 >= d)
                cur++;

            for (int v : g[u]) {
                if (f[v]) {
                    int ru = dsu.find(u), rv = dsu.find(v);

                    if (ru != rv) {
                        if (dsu.siz[ru] >= d)
                            cur--;
                        if (dsu.siz[rv] >= d)
                            cur--;

                        dsu.merge(ru, rv);

                        if (dsu.siz[ru] >= d)
                            cur++;
                    }
                }
            }
            ptr++;
        }
        ans[i] = cur;
    }

    for (int i = 1; i <= x; ++i) {
        cout << ans[i] << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    cout << fixed << setprecision(15);
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}