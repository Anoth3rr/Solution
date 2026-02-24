// Problem: D. Unfair Game
// Contest: Codeforces - Codeforces Round 1072 (Div. 3)
// URL: https://codeforces.com/contest/2184/problem/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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
constexpr int maxn = 32;

int C[maxn + 1][maxn + 1];

void init() {
    for (int i = 0; i <= maxn; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
}

void solve() {
    int n, k;
    cin >> n >> k;
    int d = __builtin_ctz(n);
    int nd = 0;
    for (int i = 0; i < d; ++i) {
        int t = k - i - 1;
        if (t < 0) continue;
        t = min(i, t);
        int sum = 0;
        for (int j = 0; j <= t; ++j) sum += C[i][j];
        nd += sum;
    }
    nd += k >= d + 1;
    cout << n - nd << endl;
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