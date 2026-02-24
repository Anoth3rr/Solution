// Problem: B. Blackslex and Showering
// Contest: Codeforces - Codeforces Round 1071 (Div. 3)
// URL: https://codeforces.com/contest/2179/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// By: Anoth3r
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {
    uniform_int_distribution<unsigned long long> dist(l, r);
    return dist(rng);
}

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    int s = 0, mx = max(abs(a[1] - a[0]), abs(a[n - 1] - a[n - 2]));
    for (int i = 1; i < n; ++i) {
        s += abs(a[i] - a[i - 1]);
    }
    for (int i = 1; i < n - 1; ++i) {
        mx = max(mx, abs(a[i] - a[i - 1]) + abs(a[i + 1] - a[i]) -
                         abs(a[i + 1] - a[i - 1]));
    }
    cout << s - mx << endl;
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