// Problem: Matrix Coloring
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126949/F
// Memory Limit: 512 MB
// Time Limit: 2000 ms
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
using ull = unsigned long long;
using int128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<ll, ll, ll>;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INf = (ll)2e18 + 9;
// constexpr ll INf = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ld eps = 1e-10;

int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0}, dy[8] = {1, 0, -1, -1, -1, 0, 1, 1};

struct DSU {
    vector<int> f, siz;

    DSU() {}
    DSU(int n) { init(n); }

    void init(int n) {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
    }

    int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        f[y] = x;
        siz[x] += siz[y];
    }

    bool same(int x, int y) { return find(x) == find(y); }

    int size(int x) { return siz[find(x)]; }
};

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (int i = 0; i < n; ++i) cin >> g[i];

    DSU dsu(n * n);
    vector<vector<int>> w(n * n);
    queue<int> q;

    auto id = [&](int x, int y) { return x * n + y; };
    auto check = [&](int x, int y) { return 0 <= x && x < n && 0 <= y && y < n; };

    auto chk = [&](int u) {
        if (g[u / n][u % n] == '1') return;
        int x = u / n, y = u % n;
        vector<int> b;
        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k * 2 + 1], ny = y + dy[k * 2 + 1];
            if (check(nx, ny) && g[nx][ny] == '1') b.pb(id(nx, ny));
        }

        bool f = true;
        if (b.size() >= 3) {
            f = false;
        } else if (b.size() == 2) {
            int x = b[0], y = b[1];
            bool ff = (abs(x / n - y / n) == 2 || abs(x % n - y % n) == 2);
            if (!ff || dsu.same(x, y)) {
                f = false;
            } else {
                w[dsu.find(x)].pb(u);
                w[dsu.find(y)].pb(u);
            }
        }

        if (!f) {
            g[x][y] = '1';
            q.push(u);
        }
    };

    auto unite = [&](int x, int y) {
        x = dsu.find(x);
        y = dsu.find(y);
        if (x == y) return;
        if (dsu.siz[x] < dsu.siz[y]) swap(x, y);
        dsu.f[y] = x;
        dsu.siz[x] += dsu.siz[y];

        for (int u : w[y]) chk(u);
        vector<int>().swap(w[y]);
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == '1') {
                int u = id(i, j);
                for (int k = 0; k < 8; ++k) {
                    int ni = i + dx[k], nj = j + dy[k];
                    if (check(ni, nj) && g[ni][nj] == '1') unite(u, id(ni, nj));
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == '0') chk(id(i, j));
        }
    }

    while (q.size()) {
        int u = q.front();
        q.pop();
        int x = u / n, y = u % n;
        for (int k = 0; k < 8; ++k) {
            int nx = x + dx[k], ny = y + dy[k];
            if (check(nx, ny) && g[nx][ny] == '1') unite(u, id(nx, ny));
        }

        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k * 2 + 1], ny = y + dy[k * 2 + 1];
            if (check(nx, ny) && g[nx][ny] == '0') chk(id(nx, ny));
        }
    }

    for (auto s : g) cout << s << endl;
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