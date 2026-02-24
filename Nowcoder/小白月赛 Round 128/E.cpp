// Problem: 扫雷难度调节
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/127255/E
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
    int n, m, k;
    cin >> n >> m >> k;

    int tot = n * m;
    int mn = tot + 1;
    int R = 0, C = 0;

    vector<bool> vis;	

    auto mark = [&](int x, int y) {
        int sr = max(x - 1, 0);
        int sc = max(y - 1, 0);
        x = min(x + 1, n - 1);
        y = min(y + 1, m - 1);

        for (int r = sr; r <= x; ++r) {
            for (int c = sc; c <= y; ++c) {
                vis[r * m + c] = 1;
            }
        }
    };

    for (int pr = 0; pr < 3; ++pr) {
        for (int pc = 0; pc < 3; ++pc) {
            vis.assign(tot, 0);

            int cnt = 0;
            for (int i = pr; i < n; i += 3) {
                for (int j = pc; j < m; j += 3) {
                    cnt++;
                    mark(i, j);
                }
            }

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (!vis[i * m + j]) {
                        cnt++;
                        mark(i, j);
                    }
                }
            }

            if (cnt < mn) {
                mn = cnt;
                R = pr;
                C = pc;
            }
        }
    }

    if (tot - mn < k) {
        cout << "-1" << endl;
    } else {
        vector<int> g(tot);
        vis.assign(tot, 0);
        int cur = 0;

        for (int i = R; i < n; i += 3) {
            for (int j = C; j < m; j += 3) {
                g[i * m + j] = 1;
                cur++;
                mark(i, j);
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!vis[i * m + j]) {
                    g[i * m + j] = 1;
                    cur++;
                    mark(i, j);
                }
            }
        }

        int res = (tot - cur) - k;

        for (int i = 0; i < tot && res > 0; ++i) {
            if (g[i] == 0) {
                g[i] = 1;
                res--;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << g[i * m + j];
            }
            cout << endl;
        }
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