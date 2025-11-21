//SakurabaEma
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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> divs(m + 1);
    for (int d = 2; d <= n; ++d) {
        for (int x = d; x <= m; x += d) divs[x].pb(d);
    }
    vector<int> dp(n + 1, -inf), b(n + 1, -inf);
    dp[0] = 0; b[0] = 0;
    vector<vector<int>> sch(m + 2);


    for (int x = 1; x <= m; ++x) {
        bool f = false;
        if (x <= n && b[x] < 0) f = true;


        vector<int> updated;
        while (!sch[x].empty()) {
            int d = sch[x].back(); sch[x].pop_back();
            if (d > n) continue;
            int prev = b[d - 1];
            if (d - 1 == x && f) prev = 0;
            if (dp[d] < prev) {
                dp[d] = prev;
                updated.pb(d);
            }
        }
        for (int d : divs[x]) {
            int prev = b[d - 1];
            if (d - 1 == x && f) prev = 0;
            int k = 0;
            int xx = x;
            while (xx % d == 0) { xx /= d; ++k; }
            int val = prev == -inf ? -inf : prev + k;
            if (val > dp[d]) { dp[d] = val; updated.pb(d); }
        }
        for (int d : updated) {
            if (dp[d] > b[d]) {
                b[d] = dp[d];
                if (x + 1 <= m + 1) sch[x + 1].pb(d + 1);
            }
        }
        if (f) {
            if (b[x] < 0) {
                b[x] = 0;
                if (x + 1 <= m + 1) sch[x + 1].pb(x + 1);
            }
        }
    }
    int ans = max(0, b[n]);
    cout << ans << "\n";
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