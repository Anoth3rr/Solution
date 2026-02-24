// Problem: 01回文
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120562/I
// Memory Limit: 2048 MB
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
using ui = unsigned;
using ull = unsigned long long;
using i128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<ll, ll, ll>;

int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

void init() {
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (int i = 0; i < n; ++i)
        cin >> g[i];
    vector<string> ans(n, string(m, 'N'));

    auto check = [&](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < m;
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < 4; ++k) {
                int nx = i + dx[k], ny = j + dy[k];
                if (check(nx, ny)) {
                    if (g[nx][ny] == g[i][j]) {
                        ans[i][j] = 'Y';
                        break;
                    }
                }
            }
        }
    }

    auto ssolve = [&](char tar) {
        vector<vector<bool>> vis(n, vector<bool>(m));
        vector<int> vis2(n * m, -1);
        int id = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (g[i][j] == tar && !vis[i][j]) {
                    id++;
                    vector<PII> nei;
                    queue<PII> q;

                    q.push({i, j});
                    vis[i][j] = 1;

                    while (!q.empty()) {
                        auto [x, y] = q.front();
                        q.pop();

                        for (int k = 0; k < 4; ++k) {
                            int nx = x + dx[k], ny = y + dy[k];

                            if (check(nx, ny)) {
                                if (g[nx][ny] == tar) {
                                    if (!vis[nx][ny]) {
                                        vis[nx][ny] = 1;
                                        q.emplace(nx, ny);
                                    }
                                } else {
                                    int idx = nx * m + ny;
                                    if (vis2[idx] != id) {
                                        vis2[idx] = id;
                                        nei.eb(nx, ny);
                                    }
                                }
                            }
                        }
                    }

                    if (nei.size() > 1) {
                        for (auto [x, y] : nei) {
                            ans[x][y] = 'Y';
                        }
                    }
                }
            }
        }
    };

    ssolve('0');
    ssolve('1');

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << endl;
    }
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