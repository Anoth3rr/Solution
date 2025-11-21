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
    int n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;
    vector<int> sa(n + 1), sb(n + 1);
    for (int i = 1; i <= n; ++i) {
        sa[i] = sa[i - 1] + (s[i - 1] == 'a');
        sb[i] = sb[i - 1] + (s[i - 1] == 'b');
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        auto it1 = lower_bound(sa.begin() + i, sa.end(), sa[i - 1] + a);
        if (it1 == sa.end()) continue;
        int r1 = it1 - sa.begin();

        auto it2 = lower_bound(sb.begin() + i, sb.end(), sb[i - 1] + b);
        int r2;
        if (it2 == sb.end()) r2 = n + 1;
        else r2 = it2 - sb.begin();

        if (r1 <= r2 - 1) {
            ans += r2 - r1;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    init();

    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    return 0;
}
