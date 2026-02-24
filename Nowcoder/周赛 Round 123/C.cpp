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
    unordered_map<int, unordered_map<char, int>> g;

    for (int i = 1; i <= n; i++) {
        int x;
        char c;
        cin >> x >> c;
        if (!g[x][c]) g[x][c] = i;
    }

    vector<PII> ans;

    for (auto v : g) {
        vector<int> vec;
        for (auto q : v.se)
            vec.pb(q.se);

        for (int i = 0; i + 1 < vec.size(); i += 2) ans.eb(vec[i], vec[i + 1]);
    }

    cout << ans.size() * 2 << endl;
    for (auto [u, v] : ans) cout << u << " " << v << endl;
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