// Problem: 终于再见
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120562/J
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

constexpr int inf = 1e9 + 7;

void init() {
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
    }

    vector<vector<int>> gp(n);
    for (int i = 1; i <= n; ++i) {
        gp[g[i].size()].pb(i);
    }

    vector<vector<int>> L;
    for (int d = 0; d < n; ++d) {
        if (!gp[d].empty()) {
            L.pb(gp[d]);
        }
    }

    vector<int> dist(n + 1, inf), ans(n + 1, -1);
    queue<int> q;

    int K = L.size();

    if (K > 0) {
        for (int u : L[K - 1]) {
            dist[u] = 0;
            q.push(u);
        }
    }

    auto bfs = [&]() {
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (dist[v] > dist[u] + 1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
    };

    bfs();

    for (int i = K - 2; i >= 0; --i) {
        for (int u : L[i]) {
            if (dist[u] != inf) {
                ans[u] = dist[u];
            } else {
                ans[u] = -1;
            }
        }

        for (int u : L[i]) {
            if (dist[u] != 0) {
                dist[u] = 0;
                q.push(u);
            }
        }
        bfs();
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
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