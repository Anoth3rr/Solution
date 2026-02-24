// Problem: 小红的基环树染色构造
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126611/F
// Memory Limit: 512 MB
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

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    vector<int> deg(n + 1);
    for (int i = 0; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
        deg[u]++, deg[v]++;
    }

    vector<int> vis(n + 1);
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 1)
            q.push(i);

    while (q.size()) {
        auto u = q.front();
        q.pop();

        vis[u] = 1;
        for (auto v : g[u]) {
            if (deg[v] > 1) {
                deg[v]--;
                if (deg[v] == 1)
                    q.push(v);
            }
        }
    }
    vector<int> cyc;
    int st = 0;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            st = i;
            break;
        }
    }

    int cur = st;
    vector<bool> vis2(n + 1);

    while (1) {
        cyc.pb(cur);
        vis2[cur] = true;

        int nxt = 0;
        for (int v : g[cur]) {
            if (!vis[v] && !vis2[v]) {
                nxt = v;
                break;
            }
        }

        if (nxt != 0) {
            cur = nxt;
        } else {
            break;
        }
    }

    vector<int> a(n + 1);
    int k = cyc.size();
    for (int i = 0; i < k; ++i) {
        int u = cyc[i];
        if (i < k - 1) {
            a[u] = (i % 2) + 1;
        } else {
            for (int c = 1; c <= 3; ++c) {
                if (c != a[cyc[i - 1]] && c != a[cyc[0]]) {
                    a[u] = c;
                    break;
                }
            }
        }
    }

    queue<int> q2;
    for (int u : cyc) {
        q2.push(u);
    }

    while (!q2.empty()) {
        int u = q2.front();
        q2.pop();

        for (int v : g[u]) {
            if (a[v] == 0) {
                for (int c = 1; c <= 3; ++c) {
                    if (c != a[u]) {
                        a[v] = c;
                        break;
                    }
                }
                q2.push(v);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
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