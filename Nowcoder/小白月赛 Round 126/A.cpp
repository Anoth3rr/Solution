// Problem: 小红打舞萌
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126282/A
// Memory Limit: 512 MB
// Time Limit: 2000 ms
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
    string a, b;
    cin >> a >> b;
    int A = 0, B = 0;
    for (auto v : a) {
        if (isdigit(v)) {
            A = A * 20 + 2 * (v - '0');
        } else {
            A++;
        }
    }
    for (auto v : b) {
        if (isdigit(v)) {
            B = B * 20 + 2 * (v - '0');
        } else {
            B++;
        }
    }
    cout << (A > B ? "Yes" : "No") << endl;
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