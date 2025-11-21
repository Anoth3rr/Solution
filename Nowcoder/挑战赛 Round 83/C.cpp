//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(),a.rend()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef __int128 lll;
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
    ll k, x, y;
    cin >> k >> x;
    ll t = x;
    vector<int> cnt;

    while (t > 0) {
        long double z = sqrtl((long double)8.0 * t + 1.0L);
        ll p = (ll)((z - 1.0L) / 2.0L);
        if (p <= 0) p = 1;
        while (p > 0 && (p * (p + 1) / 2) > t) --p;
        while (((p + 1) * (p + 2) / 2) <= t) ++p;
        cnt.pb(p);
        t -= p * (p + 1) / 2;
    }

    string ans;
    int cut = 0;
    for (int idx = 0; idx < cnt.size(); ++idx) {
        int p = cnt[idx];
        for (int t = 0; t < p; ++t) {
            for (int i = 0; i < k; ++i) cout << "(";
            for (int i = 0; i < k; ++i) cout << ")";
        }
        if (idx + 1 < cnt.size()) {
            cout << "(";
            ++cut;
        }
    }
    for (int i = 0; i < cut; ++i) cout << ")";

    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}