// Problem: Eat The Candy
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/127703/E
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
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    vector<ll> suf(n + 2);

    ll rem = a[n];
    for (int i = n - 1; i >= 1; --i) {
        ll ops = min(a[i], rem);
        suf[i] = suf[i + 1] + ops;
        rem = a[i] - ops;
    }

    ll ans = 0, S = 0;
    rem = 0;
    for (int i = 1; i <= n; ++i) {
        ll cur = a[i] + S + suf[i + 1];
        if (cur > ans)
            ans = cur;
        ll ops = min(rem, a[i]);
        S += ops;
        rem = a[i] - ops;
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