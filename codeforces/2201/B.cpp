// Problem: B. Recollect Numbers
// Contest: Codeforces - Codeforces Round 1082 (Div. 1)
// URL: https://codeforces.com/contest/2201/problem/B
// Memory Limit: 256 MB
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
    ll n, k;
    cin >> n >> k;

    if (k < n || k > 2 * n - 1) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;

    if (k == n) {
        for (int i = 1; i <= n; ++i) {
            cout << i << " " << i << " ";
        }
        cout << endl;
        return;
    }

    ll m = k - n + 1;
    vector<int> a;

    a.pb(1);
    a.pb(2);

    for (int i = 3; i <= m; ++i) {
        a.pb(i);
        a.pb(i - 2);
    }

    a.pb(m - 1);
    a.pb(m);

    for (int i = m + 1; i <= n; ++i) {
        a.pb(i);
        a.pb(i);
    }

    for (int i = 0; i < 2 * n; ++i) {
        cout << a[i] << " ";
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