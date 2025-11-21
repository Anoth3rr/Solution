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
    ll n, a, k;
    cin >> n >> a >> k;

    if (n == 1) {
        if (a == k) {
            cout << a << "\n";
        } else {
            cout << -1 << "\n";
        }
        return;
    }

    if (k < (a + 1) / 2 || k > a - (n / 2)) {
        cout << -1 << "\n";
        return;
    }

    ll L = n - 1;
    vector<ll> x(L, 0);

    for (ll i = 0; i < L; i += 2) x[i] = 1;
    if (L > 0 && x[L - 1] == 0) x[L - 1] = 1;
    ll base = 0;
    for (ll v : x) base += v;
    ll ext = k - base;
    if (L > 0) x[0] += ext;

    vector<ll> h(n, 1);
    ll res = a - n;
    for (ll i = 0; i < n; ++i) {
        ll l = (i - 1 >= 0) ? x[i - 1] : 0;
        ll r = (i < L) ? x[i] : 0;
        ll cap = l + r - 1;
        if (cap < 0) cap = 0;
        ll add = min(cap, res);
        h[i] += add;
        res -= add;
    }
    if (res != 0) {
        cout << -1 << "\n";
        return;
    }

    for (int i = 0; i < n; ++i) {
        cout << h[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}