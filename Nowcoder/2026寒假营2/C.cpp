// Problem: 炮火轰炸
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120562/C
// Memory Limit: 2048 MB
// Time Limit: 4000 ms
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

int dx[] = {1, 1, 0, -1, -1, -1, 0, 1}, dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

struct Point {
    int x, y;
    bool operator<(const Point &other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};

void init() {
}

void solve() {
    int n, q;
    cin >> n >> q;
    map<Point, int> mp;
    vector<Point> pts(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
        mp[pts[i]] = i;
    }

    vector<bool> vis(n);
    map<int, vector<PII>> Eve;

    for (int i = 0; i < n; ++i) {
        if (vis[i])
            continue;

        vector<int> comp, q = {i};
        vis[i] = 1;
        int head = 0;
        while (head < q.size()) {
            int u = q[head++];
            comp.pb(u);
            for (int k = 0; k < 8; k++) {
                Point nb = {pts[u].x + dx[k], pts[u].y + dy[k]};
                if (mp.count(nb)) {
                    int v = mp[nb];
                    if (!vis[v]) {
                        vis[v] = true;
                        q.pb(v);
                    }
                }
            }
        }

        if (comp.size() < 2)
            continue;

        int st = comp[0];
        for (int id : comp)
            if (pts[id] < pts[st])
                st = id;

        int curr = st, cd = 4, steps = 0, ms = 4 * comp.size() + 100;

        do {
            int nn = -1, nd = -1;
            for (int k = 0; k < 8; ++k) {
                int dir = (cd + k) % 8;
                Point nb = {pts[curr].x + dx[dir], pts[curr].y + dy[dir]};
                if (mp.count(nb)) {
                    nn = mp[nb];
                    nd = dir;
                    break;
                }
            }

            if (nn != -1) {
                if (pts[nn].y > pts[curr].y)
                    Eve[pts[curr].y].pb({pts[curr].x, 1});
                else if (pts[nn].y < pts[curr].y)
                    Eve[pts[nn].y].pb({pts[nn].x, -1});

                curr = nn;
                cd = (nd + 6) % 8;
            } else
                break;
            steps++;
        } while (curr != st && steps < ms);
    }

    map<int, vector<PII>> queries;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        queries[b].pb({a, i});
    }

    vector<string> ans(q, "NO");
    for (auto &[y, qs] : queries) {
        if (!Eve.count(y))
            continue;

        auto &evs = Eve[y];
        sort(all(evs));
        sort(all(qs));

        int winding = 0;
        int ptr = 0;
        for (auto &_pt : qs) {
            while (ptr < evs.size() && evs[ptr].fi < _pt.fi) {
                winding += evs[ptr].se;
                ptr++;
            }
            if (winding != 0)
                ans[_pt.se] = "YES";
        }
    }

    for (auto v : ans)
        cout << v << endl;
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