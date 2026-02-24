// Problem: 镜像
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/128672/E
// Memory Limit: 512 MB
// Time Limit: 8000 ms
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

constexpr int maxn = 1e6;

void init() {
}

void solve() {
    int a, b, k;
    cin >> a >> b >> k;
    vector<int> dist(maxn + 1, -1);
    queue<int> q;
    dist[a] = 0;
    q.push(a);

    auto rev = [&](int x) {
        int t = 0;
        while (x) {
            t = t * 10 + x % 10;
            x /= 10;
        }
        return t;
    };

    while (q.size()) {
        auto u = q.front();
        q.pop();
        if (u == b) {
            cout << dist[u] << endl;
            return;
        }
        int v = u + k;
        if (v <= maxn) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                if (v == b) {
                    cout << dist[v] << endl;
                    return;
                }
                q.push(v);
            }
        }
        if (u % 10 != 0) {
            v = rev(u);
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                if (v == b) {
                    cout << dist[v] << endl;
                    return;
                }
                q.push(v);
            }
        }
    }
    cout << -1 << endl;
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