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
constexpr int maxn = 2e5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}


vector<int> primes, spf(maxn + 1);

void init() {
    for (int i = 2; i <= maxn; ++i) {
        if (!spf[i]) primes.push_back(i), spf[i] = i;
        for (int j = 0; primes[j]*i <= maxn; ++j) {
            int m = primes[j] * i;
            spf[m] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
}

void solve() {
    int n;
    cin >> n;

    vector<int> s3_odd, s3_even;
    vector<int> bad;
    vector<int> odd;
    vector<int> even;

    for (int i = 1; i <= n; ++i) {
        if (i % 3 == 0) {
            if (i % 2 == 0) s3_even.pb(i);
            else s3_odd.pb(i);
        } else if (i == 1) {
            bad.pb(i);
        } else if (i % 2 == 0) {
            even.pb(i);
        } else {
            if (spf[i] == i && i > n / 2) {
                bad.pb(i);
            } else {
                odd.pb(i);
            }
        }
    }

    map<int, vector<int>> clu;
    for (int x : odd) {
        int target = 2 * spf[x];
        if (target > n) {
            bad.pb(x);
        } else {
            clu[target].pb(x);
        }
    }

    vector<int> occ, flx;
    for (int e : even) {
        if (clu.count(e)) occ.pb(e);
        else flx.pb(e);
    }

    vector<int> bb;
    for (int x : s3_odd) bb.pb(x);
    for (int x : s3_even) bb.pb(x);
    for (int x : flx) bb.pb(x);

    vector<int> main;
    int b_idx = 0;
    bool f = false;

    if (!bb.empty()) {
        main.pb(bb[0]);
    }

    for (int i = 0; i < (int)bb.size() - 1; ++i) {
        int u = bb[i];
        int v = bb[i + 1];

        bool ins = false;
        if (b_idx < bad.size() && !f) {
            if (__gcd(u, v) > 1) {
                main.pb(bad[b_idx++]);
                f = true;
                ins = true;
            }
        }

        if (!ins) {
            f = false;
        }

        main.pb(v);
    }

    while (b_idx < bad.size()) {
        main.pb(bad[b_idx++]);
    }

    for (int e : occ) {
        main.pb(e);
        for (int o : clu[e]) {
            main.pb(o);
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << main[i] << " ";
    }
    cout << "\n";
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