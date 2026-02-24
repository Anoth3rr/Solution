// Problem: 智乃挖坑
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120565/I
// Memory Limit: 2048 MB
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
    ll h;
    cin >> n >> m >> h;
    vector<PII> ops(m);
    for (int i = 0; i < m; ++i) {
        cin >> ops[i].fi >> ops[i].se;
    }
    auto check = [&](int t) {
        vector<ll> A(n + 2), B(n + 2);
        for (int i = 0; i < t; ++i) {
            auto [p, f] = ops[i];
            int L = max(1, p - (f - 1)), R = min(n, p + (f - 1));
            int l1 = L, r1 = min(p, R);
            if (l1 <= r1) {
                A[l1] += 1, A[r1 + 1] -= 1;
                B[l1] += f - p, B[r1 + 1] -= f - p;
            }
            int l2 = max(p + 1, L), r2 = R;
            if (l2 <= r2) {
                A[l2] += -1, A[r2 + 1] -= -1;
                B[l2] += f + p, B[r2 + 1] -= f + p;
            }
        }
        ll a = 0, b = 0;
        for (int j = 1; j <= n; ++j) {
            a += A[j];
            b += B[j];
            if (a * j + b > h)
                return 1;
        }
        return 0;
    };

    if (!check(m)) {
        cout << "No" << endl;
        return;
    }

    int lo = 1, hi = m, ans = m;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (check(mid)) {
            ans = mid;
            hi = mid - 1;
        } else
            lo = mid + 1;
    }
    cout << "Yes" << endl;
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