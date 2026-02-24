// Problem: 爱丽丝的人偶圆舞曲
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/127899/E
// Memory Limit: 512 MB
// Time Limit: 4000 ms
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

void init() {
}

void solve() {
    string s;
    cin >> s;
    int n = s.size(), mx = 0;
    for (int d = 0; d <= 13; ++d) {
        array<int, 26> dp{}, ndp{};
        for (int i = 0; i < 26; ++i)
            dp[i] = (s[0] - 'a') == i;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < 26; ++j) {
                ndp[j] = max(dp[(j - d + 26) % 26], dp[(j + d) % 26]) + (j == s[i] - 'a');
            }
            dp.swap(ndp);
        }
        for (auto v : dp)
            mx = max(mx, v);
    }
    cout << n - mx << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    cout << fixed << setprecision(15);
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}