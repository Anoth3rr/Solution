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
    int n;
    string s;
    cin >> n >> s;

    vector<int> lr(n + 1, 0), rl(n + 2, 0), ll(n + 1, 0), rr(n + 2, 0);

    for (int v = 2; v <= n; ++v) {
        if (s[v - 2] == 'R') lr[v] = lr[v - 1] + 1;
        else lr[v] = 0;
    }

    for (int v = n - 1; v >= 1; --v) {
        if (s[v - 1] == 'L') rl[v] = rl[v + 1] + 1;
        else rl[v] = 0;
    }

    for (int v = 2; v <= n; ++v) {
        if (s[v - 2] == 'L') ll[v] = ll[v - 1] + 1;
        else ll[v] = 0;
    }

    for (int v = n - 1; v >= 1; --v) {
        if (s[v - 1] == 'R') rr[v] = rr[v + 1] + 1;
        else rr[v] = 0;
    }

    vector<int> diff(n + 3, 0);
    for (int v = 1; v <= n; ++v) {
        int mn = 1 + lr[v] + rl[v];
        int mx = n - (rr[v] + ll[v]);
        diff[mn]++;
        diff[mx + 1] --;
    }


    vector<int> ans(n + 1, 0);
    int cur = 0;
    for (int i = 1; i <= n; ++i) {
        cur += diff[i];
        ans[i] = cur;
    }

    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";
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
