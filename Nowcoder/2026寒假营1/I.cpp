// Problem: AND vs MEX
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120561/I
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
using Pll = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using TllL = tuple<ll, ll, ll>;

void init() {
}

void solve() {
    ll l, r;
    cin >> l >> r;

    ll ans = r + 2;

    auto get = [&](ll l, int k) {
        ll mask = ~((1ll << (k + 1)) - 1);
        return (l & mask) | (1ll << k);
    };

    for (int k = 0; k <= 30; ++k) {
        if (!((l >> k) & 1)) {
            ll B = get(l, k), lim = r - B;

            if (lim < 0) {
                ans = min(ans, (1ll << k));
            } else {
                ll suff = lim + 1;
                if (suff < (1ll << k)) {
                    ans = min(ans, (1ll << k) + suff);
                }
            }
        }
    }

    for (int i = 0; i <= 30; ++i) {
        if ((l >> i) & 1) {
            int P = -1;
            for (int k = i + 1; k <= 31; ++k) {
                if (!((l >> k) & 1)) {
                    P = k;
                    break;
                }
            }

            if (P == -1) {
                ans = 0;
                break;
            }

            ll B = get(l, P), lim = r - B;

            if (lim < 0) {
                ans = min(ans, 0ll);
            } else {
                ll st = lim + 1;
                if (st < (1ll << P)) {
                    if ((st >> i) & 1) {
                        ll incr = (1ll << i), msk = (1ll << (i + 1)) - 1;
                        ll cand = (st + incr) & ~msk;
                        if (cand < (1ll << P)) {
                            ans = min(ans, cand);
                        }
                    } else {
                        ans = min(ans, st);
                    }
                }
            }
        }
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