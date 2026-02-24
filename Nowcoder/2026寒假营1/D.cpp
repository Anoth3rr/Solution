// Problem: Sequence Coloring
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120561/D
// Memory Limit: 1024 MB
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

constexpr int LOGN = 20;

void init() {
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1), pos;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] > 0) {
            pos.pb(i);
        }
    }

    int m = pos.size();
    if (m == 0 || k >= m) {
        cout << 0 << endl;
        return;
    }

    vector<int> nxt(m + 1);
    for (int i = 1; i <= m; ++i) {
        ll lim = pos[i - 1] + a[pos[i - 1]];
        int idx = upper_bound(all(pos), lim) - pos.begin();
        nxt[i] = max(i, idx);
    }

    vector<vector<int>> up(LOGN, vector<int>(n + 1));
    up[0][0] = 0;
    for (int i = 1; i <= m; ++i) {
        if (i == 1)
            up[0][i] = nxt[i];
        else
            up[0][i] = max(up[0][i - 1], nxt[i]);

        if (up[0][i] > m)
            up[0][i] = m;
    }

    for (int j = 1; j < LOGN; ++j) {
        for (int i = 1; i <= m; ++i) {
            up[j][i] = up[j - 1][up[j - 1][i]];
        }
    }

    auto check = [&](int t, int m) -> bool {
        int cur = 0, sds = 0;

        while (cur < m) {
            sds++;
            if (sds > k)
                return false;

            int node = cur + 1;

            for (int j = LOGN - 1; j >= 0; --j) {
                if ((t >> j) & 1) {
                    node = up[j][node];
                }
            }

            cur = node;
        }
        return true;
    };

    int lo = 0, hi = n, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (check(mid, m)) {
            ans = mid;
            hi = mid - 1;
        } else
            lo = mid + 1;
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