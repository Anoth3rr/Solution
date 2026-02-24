// Problem: B. Impost or Sus
// Contest: Codeforces - Good Bye 2025
// URL: https://codeforces.com/contest/2178/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// By: Anoth3r

#include <bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define endl "\n"
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using i128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<ll, ll, ll>;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ld eps = 1e-10;

void init() {}

void solve() {
    string s;
    cin >> s;
    int n = s.size(), cnt = 0;
    for (auto v : s) {
        cnt += v == 'u';
    }

    int keep = 0, i = 1;
    while (i <= n - 2) {
        if (s[i] == 'u') {
            int j = i;
            while (j <= n - 2 && s[j] == 'u') {
                ++j;
            }
            int L = j - i;
            keep += (L + 1) / 2;
            i = j;
        } else {
            ++i;
        }
    }

    int ans = cnt - keep;
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}