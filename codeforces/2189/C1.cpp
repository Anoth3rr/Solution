// Problem: C1. XOR Convenience (Easy Version)
// Contest: Codeforces - Codeforces Round 1075 (Div. 2)
// URL: https://codeforces.com/contest/2189/problem/C1
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

void init() {
}

void solve() {
    int n;
    cin >> n;
    if (n % 2 == 0) {
        cout << n << " ";
        for (int i = 2; i <= n - 1; ++i) {
            if (i % 2 == 0)
                cout << i + 1 << " ";
            else
                cout << i - 1 << " ";
        }
        cout << 1 << endl;
    } else {
        cout << n - 1 << " ";
        for (int i = 2; i <= n - 2; ++i) {
            if (i % 2 == 0)
                cout << i + 1 << " ";
            else
                cout << i - 1 << " ";
        }
        cout << n << " " << 1 << endl;
    }
    cout << "\n";
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