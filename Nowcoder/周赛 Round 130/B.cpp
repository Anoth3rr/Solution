// Problem: 爱丽丝的魔力零件分类
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/127899/B
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

int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

void init() {
}

void solve() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (int i = 0; i < n; ++i)
        cin >> g[i];

    bool f = false;
    auto check = [&](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < n;
    };

    for (int i = 0; i < n && !f; ++i) {
        for (int j = 0; j < n && !f; ++j) {
            if (g[i][j] == '*') {
                int cnt = 0;
                for (int k = 0; k < 4; ++k) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (check(nx, ny) && g[nx][ny] == '*')
                        ++cnt;
                }
                if (cnt == 3)
                    f = true;
            }
        }
    }
    cout << (f ? "T" : "L") << endl;
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