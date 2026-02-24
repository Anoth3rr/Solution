// Problem: 系ぎて
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120563/D
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

struct Point {
    int x, y;
    bool operator==(Point other) {
        return x == other.x && y == other.y;
    }
    bool operator!=(Point other) {
        return !(*this == other);
    }
};

int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

void init() {
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    vector<Point> p1, p2;
    for (int i = 0; i < n; ++i) {
        cin >> g[i];
        for (int j = 0; j < m; ++j) {
            if (g[i][j] == '1')
                p1.pb({i, j});
            else if (g[i][j] == '2')
                p2.pb({i, j});
        }
    }

    auto check = [&](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < m;
    };

    auto bfs = [&](Point st, Point end, vector<string> cur, char op, vector<Point> &path, vector<int> order) {
        vector<vector<Point>> pa(n, vector<Point>(m, {-1, -1}));
        vector<vector<bool>> vis(n, vector<bool>(m));
        queue<Point> q;

        q.push(st);
        vis[st.x][st.y] = true;

        bool found = false;
        while (!q.empty()) {
            Point u = q.front();
            q.pop();

            if (u == end) {
                found = true;
                break;
            }

            for (int i : order) {
                int nx = u.x + dx[i], ny = u.y + dy[i];

                if (check(nx, ny) && !vis[nx][ny]) {
                    char c = cur[nx][ny];
                    if (c != '#' && (c == '0' || c == op)) {
                        vis[nx][ny] = true;
                        pa[nx][ny] = u;
                        q.push({nx, ny});
                    }
                }
            }
        }

        if (found) {
            Point curr = end;
            while (curr != st) {
                path.pb(curr);
                curr = pa[curr.x][curr.y];
            }
            path.pb(st);
            return true;
        }
        return false;
    };

    vector<vector<int>> orders = {
        {0, 2, 3, 1},
        {1, 2, 3, 0},
        {2, 0, 1, 3},
        {3, 0, 1, 2}};

    for (auto ord : orders) {
        vector<Point> path1;
        if (bfs(p1[0], p1[1], g, '1', path1, ord)) {
            vector<string> tmp = g;
            for (auto p : path1) {
                tmp[p.x][p.y] = '#';
            }

            vector<Point> path2;
            if (bfs(p2[0], p2[1], tmp, '2', path2, {0, 1, 2, 3})) {
                cout << "YES" << endl;
                return;
            }
        }
    }

    for (auto ord : orders) {
        vector<Point> path2;
        if (bfs(p2[0], p2[1], g, '2', path2, ord)) {
            vector<string> tmp = g;
            for (auto [r, c] : path2) {
                tmp[r][c] = '#';
            }

            vector<Point> path1;
            if (bfs(p1[0], p1[1], tmp, '1', path1, {0, 1, 2, 3})) {
                cout << "YES" << endl;
                return;
            }
        }
    }
    cout << "NO" << endl;
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