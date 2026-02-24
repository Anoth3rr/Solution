//Another
#include<bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using i128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TLLL = tuple<ll, ll, ll>;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
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

    unordered_map<ll, vector<int>> mp;
    for (int i = 0; i < n; ++i) mp[a[i]].pb(i + 1);

    vector<ll> u;
    for (auto &p : mp) u.pb(p.fi);
    sort(all(u));

    int m = u.size();
    ll bs = 1;
    int bc = upper_bound(all(u), n) - u.begin();

    int r = 0;
    for (int l = 0; l < m; ++l) {
        if (r < l) r = l;
        ll R = u[l] + n - 1;
        while (r < m && u[r] <= R) ++r;
        int cnt = r - l;
        if (cnt > bc) {
            bc = cnt;
            bs = u[l];
        }
    }

    ll s = bs, R = s + n - 1;

    unordered_map<ll, int> used;
    vector<bool> keep(n + 1, 0);

    for (ll x = s; x <= R; ++x) {
        if (mp.count(x) && !mp[x].empty()) {
            int id = mp[x].back();
            mp[x].pop_back();
            keep[id] = 1;
            used[x] = 1;
        }
    }

    vector<ll> need;
    
    vector<int> chg;
    for (ll x = s; x <= R; ++x)
        if (!used.count(x)) need.pb(x);

    for (int i = 1; i <= n; ++i)
        if (!keep[i]) chg.pb(i);

    cout << chg.size() << endl;
    for (int i = 0; i < chg.size(); ++i) cout << chg[i] << " " << need[i] << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}