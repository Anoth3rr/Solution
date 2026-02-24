// Problem: C2. XOR-convenience (Hard Version)
// Contest: Codeforces - Codeforces Round 1075 (Div. 2)
// URL: https://codeforces.com/contest/2189/problem/C2
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
    if ((n & (n - 1)) == 0) {
        cout << "-1" << endl;
        return;
    }
    vector<int> p(n + 1);
    vector<bool> vis(n + 1);
    p[n] = n;
    vis[n] = 1;
    for (int i = n - 1; i >= 1; --i) {
        bool ok = false;
        for (int a = 1; a <= n; ++a) {
            if (!vis[a] && ((a ^ i) >= 1 && (a ^ i) <= n) && vis[a ^ i]) {
                p[i] = a;
                vis[a] = 1;
                ok = true;
                break;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << p[i] << " ";
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