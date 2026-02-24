// Problem: 立希的扫雷构造
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120564/E
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

bool vis[10][10];
vector<int> mans[10][10], mend[10][10], mtr[10][10];

void init() {
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    bool sw = false;
    if (n < m) {
        swap(n, m);
        sw = true;
    }
    if (!vis[n][m]) {
        int len = n * m, lim = 1 << (m + 1), sz = lim * (len + 1);

        mtr[n][m].resize(len * sz);
        mans[n][m].assign(len + 1, -1);
        mend[n][m].assign(len + 1, -1);

        vector<int> dp(sz, -1);
        dp[0] = 0;

        auto id = [&](int s, int k) {
            return s * (len + 1) + k;
        };

        for (int p = 0; p < len; ++p) {
            int r = p / m, c = p % m;
            vector<int> ndp(sz, -1);
            int base = p * sz;

            bool hl = c > 0;
            bool htl = r > 0 && c > 0;
            bool ht = r > 0;
            bool htr = r > 0 && c < m - 1;

            for (int s = 0; s < lim; ++s) {
                for (int j = 0; j <= p; ++j) {
                    if (dp[id(s, j)] == -1)
                        continue;

                    for (int v = 0; v < 2; ++v) {
                        int nj = j + v;

                        int add = 0;
                        if (hl)
                            add += ((s >> 0) & 1) ^ v;
                        if (htl)
                            add += ((s >> m) & 1) ^ v;
                        if (ht)
                            add += ((s >> (m - 1)) & 1) ^ v;
                        if (htr)
                            add += ((s >> (m - 2)) & 1) ^ v;

                        int ns = ((s << 1) & (lim - 1)) | v;
                        int val = dp[id(s, j)] + add;
                        int nidx = id(ns, nj);

                        if (val > ndp[nidx]) {
                            ndp[nidx] = val;
                            int drop = (s >> m) & 1;
                            mtr[n][m][base + nidx] = (drop << 1) | v;
                        }
                    }
                }
            }
            dp = move(ndp);
        }
        
        for (int s = 0; s < lim; ++s) {
            for (int j = 0; j <= len; ++j) {
                int val = dp[id(s, j)];
                if (val > mans[n][m][j]) {
                    mans[n][m][j] = val;
                    mend[n][m][j] = s;
                }
            }
        }
        vis[n][m] = true;
    }

    cout << mans[n][m][k] << endl;
    vector<string> g(n, string(m, '.'));
    int cs = mend[n][m][k], ck = k;
    int len = n * m, lim = 1 << (m + 1), sz = lim * (len + 1);

    auto id = [&](int s, int k) {
        return s * (len + 1) + k;
    };

    for (int p = len - 1; p >= 0; --p) {
        int info = mtr[n][m][p * sz + id(cs, ck)];

        int v = info & 1;
        int drop = (info >> 1) & 1;

        if (v)
            g[p / m][p % m] = '*';

        cs = (cs >> 1) | (drop << m);
        ck -= v;
    }

    if (sw) {
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i)
                cout << g[i][j];
            cout << endl;
        }
    } else {
        for (int i = 0; i < n; ++i)
            cout << g[i] << endl;
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