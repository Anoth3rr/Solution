// Problem: D1. Little String (Easy Version)
// Contest: Codeforces - Codeforces Round 1075 (Div. 2)
// URL: https://codeforces.com/contest/2189/problem/D1
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

constexpr int MOD = 1e9 + 7;

ll mul(ll a, ll b, ll p) {
    __int128 res = (__int128)a * b;
    res %= p;
    return res;
}

void init() {
}

void solve() {
    int n;
    ll c;
    string s;
    cin >> n >> c >> s;
    if (s[0] == '0' || s[n - 1] == '0') {
        cout << "-1" << endl;
        return;
    }
    ll a = 1 % c, b = 1;
    for (int i = 1; i <= n - 1; i++) {
        ll f = (s[i - 1] == '1') ? 2 : (i - 1);
        a = mul(a, f, c);
        b = mul(b, f, MOD);
    }
    if (a % c == 0)
        cout << "-1" << endl;
    else
        cout << b << endl;
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