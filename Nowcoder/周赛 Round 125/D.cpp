// Problem: 小苯的01合并
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126418/D
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
    string A, B;
    cin >> A >> B;
    int a = 0, b = 0;
    for (auto v : A) {
        a ^= v - '0';
    }
    for (auto v : B) {
        b ^= v - '0';
    }
    if (a != b) {
        cout << "NO" << endl;
        return;
    }
    int pos = 0;
    bool ok = true;

    for (int i = 0; i < m - 1; i++) {
        int cur = 0;
        bool f = false;

        for (int j = pos; j <= n - (m - i - 1) - 1; j++) {
            cur ^= (A[j] - '0');
            if (cur == (B[i] - '0')) {
                pos = j + 1;
                f = true;
                break;
            }
        }

        if (!f) {
            ok = false;
            break;
        }
    }

    if (!ok) {
        cout << "NO" << endl;
        return;
    }

    int cur = 0;
    for (int i = pos; i < n; i++) {
        cur ^= (A[i] - '0');
    }

    if (cur == (B[m - 1] - '0')) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
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