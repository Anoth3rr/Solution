// Problem: 夜揽星河入梦
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126120/C
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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    if (n + 1 < m) {
        cout << "NO" << endl;
        return;
    }
    sort(all(a));

    bool f = false;
    int l = 0;

    for (int r = 0; r < n; r++) {
        while (l < r) {
            if (a[r] - a[l] - r + l <= 1)
                break;
            l++;
        }
        if (r - l + 1 >= m - 1 && a[r] - a[l] - r - l <= 1) {
            f = true;
            break;
        }
    }

    cout << (f ? "YES" : "NO") << endl;
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