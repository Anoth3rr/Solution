// Problem: 小L的数组
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120566/H
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
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        cin >> b[i];
    array<bool, 2048> dp{}, ndp{};
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        fill(all(ndp), 0);
        int ai = a[i], bi = b[i];
        for (int x = 0; x < 2048; ++x) {
            if (!dp[x])
                continue;
            int y1 = max(0, x - a[i]);
            ndp[y1] = 1;
            int y2 = x ^ b[i];
            ndp[y2] = 1;
        }
        dp.swap(ndp);
    }
    int ans = 0;
    for (int x = 2047; x >= 0; --x) {
        if (dp[x]) {
            ans = x;
            break;
        }
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