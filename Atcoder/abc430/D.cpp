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
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    set<ll> pos;
    unordered_map<ll, ll> d;
    pos.insert(0);
    d[0] = 0;
    ll S = 0;

    for (int i = 0; i < n; ++i) {
        ll x = a[i];
        auto it = pos.lower_bound(a[i]);
        bool f1 = (it != pos.end()), f2 = (it != pos.begin());

        auto pref = f2 ? prev(it) : pos.end();

        if (f2) {
            ll pred = *pref;
            ll old = d[pred];
            ll ppd = INF;
            if (pref != pos.begin()) {
                auto pp = prev(pref);
                ppd = pred - *pp;
            }
            ll npd = min(ppd, a[i] - pred);
            S += (npd - old);
            d[pred] = npd;
        }

        if (f1) {
            ll succ = *it;
            ll old = d[succ];
            ll nnd = INF;
            auto nit = next(it);
            if (nit != pos.end()) nnd = *nit - succ;
            ll nsd = min(nnd, succ - a[i]);
            S += (nsd - old);
            d[succ] = nsd;
        }

        ll l = f2 ? a[i] - *pref : INF;
        ll r = f1 ? *it - a[i] : INF;
        ll nxd = min(l, r);
        d[a[i]] = nxd;
        S += nxd;
        pos.insert(a[i]);

        cout << S << "\n";
    }
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
