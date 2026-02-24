// Problem: 左右左右左左右，左右左左右
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/127255/C
// Memory Limit: 512 MB
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

constexpr ll INF = 2e18;

void init() {
}

void solve() {
    int n;
    ll x, y;
    cin >> n >> x >> y;
    if (x == y && x == 0) {
        cout << string(n, '0') << endl;
        return;
    }
    string ans;
    ll S = 0;
    for (int i = 1; i <= n; ++i) {
        if (llabs(S - y) <= S + x) {
            ans += '0';
            S -= y;
        } else {
            ans += '1';
            S += x;
        }
    }
    cout << ans << endl;
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