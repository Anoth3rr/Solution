// Problem: 时不时使使用玉米加农炮掩饰害羞的邻座艾莉同学
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120564/H
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

int dx[] = {-2, -1, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 2}, dy[] = {0, -1, 0, 1, -2, -1, 0, 1, 2, -1, 0, 1, 0};

void init() {
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> g(n, vector<ll>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> g[i][j];

    vector<ll> sum(n * m);

    auto id = [&](int x, int y) {
        return x * m + y;
    };

    auto check = [&](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < m;
    };

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (g[x][y] == 0)
                continue;
            ll v = g[x][y];
            for (int k = 0; k < 13; ++k) {
                int nx = x + dx[k], ny = y + dy[k];
                if (check(nx, ny)) {
                    sum[id(nx, ny)] += v;
                }
            }
        }
    }
    priority_queue<PLL> pq;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            pq.emplace(sum[id(i, j)], id(i, j));

    while (q--) {
        int x, y;
        ll z;
        cin >> x >> y >> z;
        x--, y--;
        g[x][y] += z;
        for (int k = 0; k < 13; ++k) {
            int nx = x + dx[k], ny = y + dy[k];
            if (check(nx, ny)) {
                sum[id(nx, ny)] += z;
                pq.emplace(sum[id(nx, ny)], id(nx, ny));
            }
        }
        while (!pq.empty()) {
            auto [v, id] = pq.top();
            if (sum[id] == v) {
                cout << id / m + 1 << " " << id % m + 1 << endl;
                break;
            } else
                pq.pop();
        }
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