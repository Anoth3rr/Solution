//Anoth3r
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
    int n; cin >> n;
    vector<int> a1(n + 1), a2(n + 1);
    for (int i = 1; i <= n; i++) cin >> a1[i];
    for (int i = 1; i <= n; i++) cin >> a2[i];
    int M = 2 * n;
    vector<vector<PII>> pos(M + 1);
    for (int j = 1; j <= n; j++) {
        pos[a1[j]].pb({1, j});
        pos[a2[j]].pb({2, j});
    }
    vector<char> tp(n + 1, 0), bt(n + 1, 0);
    int ft = 1;
    int lb = n;
    ll ans = 0;
    int r = 0;
    for (int l = 1; l <= M; ++l) {
        while (r < M && !(ft >= lb + 2)) {
            ++r;
            for (auto [x, y] : pos[r]) {
                if (x == 1) {
                    if (!tp[y]) {
                        tp[y] = 1;
                        while (ft <= n && tp[ft]) ++ft;
                    }
                } else {
                    if (!bt[y]) {
                        bt[y] = 1;
                        while (lb >= 1 && bt[lb]) --lb;
                    }
                }
            }
        }
        if (ft >= lb + 2) {
            ans += (ll)(M - r + 1);
        }
        for (auto [x, y] : pos[l]) {
            if (x == 1) {
                if (tp[y]) {
                    tp[y] = 0;
                    if (y < ft) ft = y;
                }
            } else {
                if (bt[y]) {
                    bt[y] = 0;
                    if (y > lb) lb = y;
                }
            }
        }
        if (r < l) r = l - 1;
    }
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
