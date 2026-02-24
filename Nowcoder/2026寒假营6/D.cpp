// Problem: 小L的扩展
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120566/D
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

constexpr ll INF = 4e18;

int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

void init() {
}

void solve() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;

    int N = n * m;
    vector<ll> T(N), dist(N, INF);

    priority_queue<PLL> pq;

    auto id = [&](int x, int y) {
        return x * m + y;
    };

    for (int i = 0; i < a; ++i) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        dist[id(x, y)] = 0;
        pq.push({0, id(x, y)});
    }

    for (int i = 0; i < b; ++i) {
        int x, y, t;
        cin >> x >> y >> t;
        x--, y--;
        T[id(x, y)] = t;
    }

    auto check = [&](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < m;
    };

    while (pq.size()) {
        auto [d, u] = pq.top();
        pq.pop();
        d = -d;
        if (d > dist[u])
            continue;

        int x = u / m, y = u % m;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];

            if (check(nx, ny)) {
                int v = id(nx, ny);

                ll time = max(d + 1, T[v]);

                if (time < dist[v]) {
                    dist[v] = time;
                    pq.push({-time, v});
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        ans = max(ans, dist[i]);
    }

    cout << ans << endl;
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