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

template <class T> T sign(const T &a) {
    return a == 0 ? 0 : (a < 0 ? -1 : 1);
}

void init() {

}

void solve() {
    int n;
    cin >> n;
    ll mn1 = INF, mn2 = INF;
    for (int i = 0; i < n; ++i) {
        ll x, y;
        cin >> x >> y;
        mn1 = min(mn1, x + y);
        mn2 = min(mn2, -x + y);
    }
    ll _, sum, minus;

    cout << "? D 1000000000" << endl, cin>>_;
    cout << "? L 1000000000" << endl, cin>>_;
    cout << "? D 1000000000" << endl, cin>>_;
    cout << "? L 1000000000" << endl, cin>>sum;
    sum = mn1 + 4e9 - sum;

    cout << "? R 1000000000" << endl, cin>>_;
    cout << "? R 1000000000" << endl, cin>>_;
    cout << "? R 1000000000" << endl, cin>>_;
    cout << "? R 1000000000" << endl, cin>>minus;
    minus = mn2 + 4e9 - minus;
    cout << "! " << (sum - minus) / 2 << " " << (sum + minus) / 2 << endl;
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