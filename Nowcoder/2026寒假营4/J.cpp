// Problem: 立希坐地铁
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120564/J
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

constexpr ll INF = 4e18;

struct Pt {
    int x, y;
    bool tr;
};

void init() {
}

void solve() {
    int n, m;
    cin >> n >> m;
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;

    vector<Pt> pts;
    map<PII, int> pid;

    auto get = [&](int x, int y) {
        if (pid.find({x, y}) == pid.end()) {
            pid[{x, y}] = pts.size();
            pts.pb({x, y, false});
        }
        return pid[{x, y}];
    };

    int sid = get(sx, sy), eid = get(ex, ey);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        int id = get(u, v);
        pts[id].tr = true;
    }

    int k = pts.size(), virt = 6 * k, tot = 7 * k;
    vector<vector<PLL>> g(tot);

    for (int i = 0; i < k; ++i) {
        if (pts[i].tr) {
            int vn = virt + i;
            for (int d = 0; d < 6; ++d) {
                g[i * 6 + d].pb({vn, 0});
                g[vn].pb({i * 6 + d, 1});
            }
        }
    }

    vector<vector<PII>> rs(n + 1), cs(n + 1);
    vector<vector<PLL>> rgs(n / 2 + 1);

    for (int i = 0; i < k; ++i) {
        rs[pts[i].x].pb({pts[i].y, i});
        cs[pts[i].y].pb({pts[i].x, i});

        int k = min({pts[i].x, n - pts[i].x + 1, pts[i].y, n - pts[i].y + 1});
        ll s = n - 2 * k + 1;
        ll pos = 0;
        if (pts[i].x == k)
            pos = pts[i].y - k;
        else if (pts[i].y == n - k + 1)
            pos = s + (pts[i].x - k);
        else if (pts[i].x == n - k + 1)
            pos = 2 * s + (n - k + 1 - pts[i].y);
        else
            pos = 3 * s + (n - k + 1 - pts[i].x);
        rgs[k].pb({pos, i});
    }

    for (int i = 1; i <= n; ++i) {
        sort(all(rs[i]));
        for (int j = 0; j + 1 < rs[i].size(); ++j) {
            int u = rs[i][j].se, v = rs[i][j + 1].se;
            ll d = 2ll * (rs[i][j + 1].fi - rs[i][j].fi);
            g[u * 6 + 0].pb({v * 6 + 0, d});
            g[v * 6 + 1].pb({u * 6 + 1, d});
        }
    }
    for (int i = 1; i <= n; ++i) {
        sort(all(cs[i]));
        for (int j = 0; j + 1 < cs[i].size(); ++j) {
            int u = cs[i][j].se, v = cs[i][j + 1].se;
            ll d = 2ll * (cs[i][j + 1].fi - cs[i][j].fi);
            g[u * 6 + 2].pb({v * 6 + 2, d});
            g[v * 6 + 3].pb({u * 6 + 3, d});
        }
    }
    for (int k = 1; k <= n / 2; ++k) {
        if (rgs[k].empty())
            continue;
        sort(all(rgs[k]));
        ll len = 4LL * (n - 2 * k + 1);
        int sz = rgs[k].size();
        for (int i = 0; i < sz; ++i) {
            int u = rgs[k][i].se;
            int v = rgs[k][(i + 1) % sz].se;
            ll d = (rgs[k][(i + 1) % sz].fi - rgs[k][i].fi + len) % len;
            if (d == 0 && len > 0)
                d = len;
            g[u * 6 + 4].pb({v * 6 + 4, 2 * d});
            g[v * 6 + 5].pb({u * 6 + 5, 2 * d});
        }
    }

    priority_queue<PLL, vector<PLL>, greater<PLL>> pq;
    vector<ll> dist(tot, INF);
    vector<int> par(tot, -1);
    for (int d = 0; d < 6; ++d) {
        dist[sid * 6 + d] = 0;
        pq.push({0, sid * 6 + d});
    }

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u])
            continue;
        for (auto &[v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                par[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    ll ans = INF;
    int edn = -1;
    for (int d = 0; d < 6; ++d) {
        if (dist[eid * 6 + d] < ans) {
            ans = dist[eid * 6 + d];
            edn = eid * 6 + d;
        }
    }

    if (ans == INF) {
        cout << "Impossible!" << endl;
        return;
    }

    cout << ans << endl;

    vector<int> path;
    for (int u = edn; u != -1; u = par[u])
        path.pb(u);
    reverse(all(path));

    string ss = "EWSNCI";
    vector<pair<char, int>> segs;
    int cd = path[0] % 6;

    for (int i = 0; i < path.size(); ++i) {
        if (path[i] >= virt) {
            int u = path[i - 1] / 6;
            segs.pb({ss[cd], u});
            if (i + 1 < path.size())
                cd = path[i + 1] % 6;
        }
    }
    segs.pb({ss[cd], path.back() / 6});

    cout << segs.size() << endl;
    cout << sx << " " << sy << endl;
    for (auto [u, v] : segs) {
        cout << u << endl;
        cout << pts[v].x << " " << pts[v].y << endl;
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