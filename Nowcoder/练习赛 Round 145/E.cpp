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
typedef ll i128;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef tuple<ll, ll, ll> TLLL;
typedef __gnu_pbds::tree<PLL, __gnu_pbds::null_type, less<PLL>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
constexpr ll MOD = 998244353;
constexpr ld PI = acos(-1.0);
constexpr ld eps = 1e-10;
constexpr ll LIM = (ll)1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

void init() {

}

void solve() {
    ll n;
    cin >> n;
    ll r = 2, s = 1;

    ll prn = 1;
    for (int i = 0; i < n; i++) prn *= r;
    ll psn = 1;

    ll d = prn - psn;
    ll t0 = n * psn;

    vector<ll> X(n), Y(n);
    for (ll i = 0; i < n; i++) {
        ll pt = t0 + i * d;

        ll ai = r * pt;
        ll ti = t0 + (i + 1) * d;
        ll bi = s * ti;

        if (ai > LIM || ai < -LIM || bi > LIM || bi < -LIM) {
            cout << "-1 -1" << "\n";
            return;
        }
        X[i] = ai;
        Y[i] = bi;
    }

    unordered_set<ll> seen;
    for (auto v : X) seen.insert(v);
    for (auto v : Y) if (seen.count(v)) {
            cout << "-1 -1" << "\n";
            return;
        }

    for (int i = 0; i < n; i++) {
        cout << X[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << Y[i] << " ";
    }
    cout << "\n";
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
