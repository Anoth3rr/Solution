//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef __int128 i128;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef tuple<ll, ll, ll> TLLL;
typedef __gnu_pbds::tree<PLL, __gnu_pbds::null_type, less<PLL>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;
// typedef __gnu_pbds::tree<ll, __gnu_pbds::null_type, less<ll>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ld PI = acos(-1.0);
constexpr ld eps = 1e-10;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

void init() {

}

void solve() {
    int n;
    string s;
    cin >> n >> s;
    vector<vector<int>> dp(n, vector<int>(n, -inf)), lcp(n + 1, vector<int>(n + 1));
    vector<vector<PII>> segs(n);
    vector<int> idx(n), mx(n, -inf);
    vector<bool> vis(n);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            if (s[i] == s[j]) lcp[i][j] = 1 + lcp[i + 1][j + 1];
            else lcp[i][j] = 0;
        }
    }
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i <= j; ++i) {
            if (i == 0) {
                dp[i][j] = 1;
                continue;
            }
            if (!vis[i]) {
                vector<PII> v;
                for (int k = 0; k < i; ++k) {
                    int prev = dp[k][i - 1];
                    if (prev <= -inf / 2) continue;
                    int la = i - k;
                    int t = lcp[k][i];
                    int mn;
                    if (t >= la) mn = la;
                    else {
                        if (s[i + t] > s[k + t]) mn = t + 1;
                        else mn = n + 5;
                    }
                    if (mn <= n) v.eb(mn, prev);
                }
                sort(all(v));
                segs[i] = move(v);
                idx[i] = 0;
                mx[i] = -inf;
                vis[i] = 1;
            }
            int len = j - i + 1;
            auto &vec = segs[i];
            while (idx[i] < vec.size() && vec[idx[i]].fi <= len) {
                mx[i] = max(mx[i], vec[idx[i]].se);
                ++idx[i];
            }
            if (mx[i] > -inf / 2) {
                dp[i][j] = max(dp[i][j], mx[i] + 1);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) ans = max(ans, dp[i][n - 1]);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    init();

    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    return 0;
}