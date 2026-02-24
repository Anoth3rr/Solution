// Problem: 进退的艺术
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/127255/D
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
    ll m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i], b[i] = a[i];
    sort(all(b));
    vector<ll> pre(n + 1);
    for (int i = 0; i < n; i++)
        pre[i + 1] = pre[i] + b[i];
    for (int i = 0; i < n; i++) {
        ll p = upper_bound(all(b), m - a[i]) - b.begin();
        ll ans = p * a[i] - pre[n] + pre[p];
        if (2 * a[i] <= m) {
            ans -= a[i];
        } else {
            ans += a[i];
        }

        cout << ans << " ";
    }
    cout << endl;
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