// Problem: 竹摇清风拂面
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126120/F
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
    int n;
    string s;
    cin >> n >> s;
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    if (n & 1) {
        cout << -1 << endl;
        return;
    }

    vector<int> freq(26, 0);
    for (char c : s)
        freq[c - 'a']++;
    bool f = true;
    for (auto v : freq)
        if (v & 1) {
            f = false;
            break;
        }
    if (!f) {
        cout << -1 << endl;
        return;
    }

    string ss = s + s;
    vector<ll> aa(2 * n);
    for (int i = 0; i < n; ++i)
        aa[i] = a[i], aa[i + n] = a[i];

    vector<vector<ll>> dp(2 * n, vector<ll>(2 * n, INF));

    for (int len = 2; len <= n; len += 2) {
        for (int l = 0; l + len - 1 < 2 * n; ++l) {
            int r = l + len - 1;
            for (int k = l + 1; k <= r; k += 2) {
                if (ss[l] != ss[k])
                    continue;
                ll L = 0;
                if (l + 1 <= k - 1) {
                    L = dp[l + 1][k - 1];
                    if (L == INF)
                        continue;
                }
                ll R = 0;
                if (k + 1 <= r) {
                    R = dp[k + 1][r];
                    if (R == INF)
                        continue;
                }
                ll c = L + R + aa[l] * aa[k];
                if (c < dp[l][r])
                    dp[l][r] = c;
            }
        }
    }

    ll ans = INF;
    for (int st = 0; st < n; ++st)
        ans = min(ans, dp[st][st + n - 1]);
    if (ans == INF)
        cout << -1 << endl;
    else
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