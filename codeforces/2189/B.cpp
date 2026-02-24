// Problem: B. The Curse of the Frog
// Contest: Codeforces - Codeforces Round 1075 (Div. 2)
// URL: https://codeforces.com/contest/2189/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// By: Entelechia

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
    ll x;
    cin >> n >> x;
    ll t = 0, p = 0;
    for (int i = 0; i < n; ++i) {
        ll a, b, c;
        cin >> a >> b >> c;
        t += (b - 1) * a;
        p = max(p, b * a - c);
    }
    if (t >= x)
        cout << 0 << endl;
    else if (p <= 0)
        cout << -1 << endl;
    else {
        cout << (x - t + p - 1) / p << endl;
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