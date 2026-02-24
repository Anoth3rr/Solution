// Problem: arrangement
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/119900/C
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
    int n;
    cin >> n;
    vector<int> p(n), id(n), d(n), pos(n), p2(n);
    for (int i = 0; i < n; ++i)
        cin >> p[i], --p[i];
    for (int i = 0; i < n; ++i)
        cin >> id[i], --id[i];
    for (int i = 0; i < n; ++i)
        cin >> d[i], --d[i];
    for (int i = 0; i < n; ++i)
        pos[d[i]] = i;
    for (int i = 0; i < n; ++i)
        p2[i] = pos[p[i]];

    vector<bool> vis(n);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int x = id[i];
        while (!vis[x]) {
            vis[x] = 1;
            ++cnt;
            x = p2[x];
        }
        cout << cnt << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}