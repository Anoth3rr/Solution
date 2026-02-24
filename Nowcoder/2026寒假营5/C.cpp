// Problem: 智乃的草坪
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120565/C
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

constexpr ld INF = 1e12l;
constexpr ld eps = 1e-12l;

void init() {
}

void solve() {
    int n, k;
    ld r, c;
    cin >> n >> k >> r >> c;
    vector<pair<ld, ld>> pts(n);
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].fi >> pts[i].se;
    }

    auto check = [&](ld t) {
        vector<pair<ld, ld>> segs;
        for (auto [p, v] : pts) {
            ld R = v * t;
            if (R + eps < r)
                continue;
            ld h = sqrt(max(0.0l, R * R - r * r));
            ld L = p - h, Rr = p + h;
            segs.eb(L, Rr);
        }
        if (segs.empty())
            return false;
        sort(all(segs));
        ld cur = 0.0l;
        int used = 0, idx = 0;
        int m = segs.size();
        while (cur + eps < c && used < k) {
            ld mx = cur;
            while (idx < m && segs[idx].fi <= cur + eps) {
                if (segs[idx].se > mx)
                    mx = segs[idx].se;
                ++idx;
            }
            if (mx <= cur + eps)
                break;
            cur = mx;
            ++used;
        }
        return (cur + eps >= c);
    };

    ld lo = 0.0l, hi = INF, ans = hi;
    for (int it = 0; it < 1000; ++it) {
        ld mid = (lo + hi) / 2.0l;
        if (check(mid))
            ans = mid, hi = mid;
        else
            lo = mid;
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