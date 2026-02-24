// Problem: 小R的min
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/119900/E
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
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i], b[i] = a[i];
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    int k = b.size();

    vector<PII> qs(m);
    vector<int> ans(m), L(m), R(m, k - 1);

    auto S = [&](int x) {
        return x <= 0 ? 0ll : 1ll * x * (x + 1) / 2;
    };

    auto calc = [&](int a, int b, int c, int d) {
        return S(min(b, d) - max(a, c) + 1);
    };

    for (int i = 0; i < m; ++i)
        cin >> qs[i].fi >> qs[i].se, qs[i].fi--, qs[i].se--;

    for (int _ = 0; _ < 10; ++_) {
        bool f = false;
        vector<vector<int>> mid(k);

        for (int i = 0; i < m; ++i) {
            if (L[i] <= R[i]) {
                mid[(L[i] + R[i] + 1) / 2].pb(i);
                f = true;
            }
        }
        if (!f)
            break;

        for (int i = 0; i < k; ++i) {
            if (mid[i].empty())
                continue;
            int v = b[i];

            vector<PII> seg;
            vector<ll> pre;
            pre.pb(0);

            for (int j = 0; j < n;) {
                if (a[j] >= v) {
                    int st = j;
                    while (j < n && a[j] >= v)
                        j++;
                    ll w = S(j - st);
                    seg.eb(st, j - 1);
                    pre.pb(pre.back() + w);
                } else {
                    j++;
                }
            }

            for (int id : mid[i]) {
                auto [l, r] = qs[id];
                ll tar = (S(r - l + 1) + 1) / 2;
                ll cnt = 0;

                int il = lower_bound(all(seg), l, [&](auto a, int v) { return a.se < v; }) - seg.begin();
                int ir = upper_bound(all(seg), r, [&](int v, auto b) { return v < b.fi; }) - seg.begin() - 1;

                if (il <= ir) {
                    if (il == ir) {
                        cnt += calc(seg[il].fi, seg[il].se, l, r);
                    } else {
                        cnt += calc(seg[il].fi, seg[il].se, l, r);
                        cnt += calc(seg[ir].fi, seg[ir].se, l, r);
                        if (il + 1 <= ir - 1)
                            cnt += pre[ir] - pre[il + 1];
                    }
                }

                if (cnt >= tar) {
                    ans[id] = v;
                    L[id] = i + 1;
                } else {
                    R[id] = i - 1;
                }
            }
        }
    }

    for (auto x : ans)
        cout << x << endl;
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