// Problem: 小红出勤
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126282/C
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
    int n, p, k;
    cin >> n >> p >> k;

    map<string, int> cnt;
    ll tot = 0;

    for (int i = 0; i < n; i++) {
        string s;
        int a;
        cin >> s >> a;
        cnt[s] = a;
        tot += a;
    }

    int mx = inf;
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        mx = min(mx, cnt[s]);
    }

    if (p < k) {
        cout << -1 << endl;
        return;
    }

    ll mn = (tot + p - 1) / p;

    if (mn > mx) {
        cout << -1 << endl;
    } else {
        cout << mn << " " << mx << endl;
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