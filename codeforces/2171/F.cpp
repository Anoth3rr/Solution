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
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    vector<int> suff(n);
    suff[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; --i) {
        if (p[i] > p[suff[i + 1]]) {
            suff[i] = i;
        } else {
            suff[i] = suff[i + 1];
        }
    }

    vector<int> pref;
    int mn = n + 1;
    for (int i = 0; i < n; ++i) {
        if (p[i] < mn) {
            mn = p[i];
            pref.pb(i);
        }
    }

    for (int k = 0; k < pref.size() - 1; ++k) {
        if (p[pref[k]] > p[suff[pref[k + 1]]]) {
            cout << "No" << "\n";
            return;
        }
    }

    cout << "Yes" << "\n";

    int cur = 0;
    for (int i = 1; i < n; ++i) {
        if (cur + 1 < pref.size() && i == pref[cur + 1]) {
            cur++;
        } else {
            cout << p[pref[cur]] << " " << p[i] << "\n";
        }
    }

    for (int k = 0; k < pref.size() - 1; ++k) {
        cout << p[pref[k]] << " " << p[suff[pref[k + 1]]] << "\n";
    }
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
