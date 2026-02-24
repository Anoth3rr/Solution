// Problem: 小红的奇数奶油球
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/127240/D
// Memory Limit: 512 MB
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

void init() {
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    if (n == 1) {
        cout << 1 << endl;
        return;
    }
    vector<int> siz(n + 1), fa(n + 1);
    function<void(int, int)> dfs = [&](int u, int p) {
        siz[u] = 1;
        fa[u] = p;
        for (auto v : g[u]) {
            if (v == p)
                continue;
            dfs(v, u);
            siz[u] += siz[v];
        }
    };
    dfs(1, 0);
    int ans = 0;
    for (int u = 1; u <= n; ++u) {
        int o = n - 1;
        bool f = true;
        for (auto v : g[u]) {
            if (v == fa[u])
                continue;
            if (!(siz[v] & 1)) {
                f = false;
                break;
            }
            o -= siz[v];
        }
        if (f && ((o & 1) || o == 0))
            ans++;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    cin >> t;
    cout << fixed << setprecision(15);
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}