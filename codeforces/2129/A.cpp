//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(),a.rend();
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

struct DSU {
    vector<ll> fa, siz;
    int n;

    DSU() {}
    DSU(ll n_): n(n_) {
        init(n);
    }

    void init(ll n) {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        siz.assign(n, 1);
    }

    ll find(ll x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);;
    }

    bool same(ll x, ll y) {
        return find(x) == find(y);
    }

    bool merge(ll x, ll y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        fa[y] = x;
        return true;
    }

    ll size(ll x) {
        return siz[find(x)];
    }

    ll count() {
        ll cnt = 0;
        for (int i = 0; i < n; ++i) {
            cnt += fa[i] == i;
        }
        return cnt;
    }
};

void init() {

}

void solve() {
    int n;
    cin >> n;
    vector<PII> seg(n);
    for (int i = 0; i < n; i++) {
        cin >> seg[i].fi >> seg[i].se;
    }
    vector<int> idx(n);
    iota(all(idx), 0);
    sort(all(idx), [&](int i, int j) {
        if (seg[i].se != seg[j].se) return seg[i].se < seg[j].se;
        return seg[i].fi > seg[j].fi;
    });

    DSU dsu(2 * n + 5);
    vector<char> covered(2 * n + 5, 0);
    vector<int> ans;

    for (int i : idx) {
        int a = seg[i].fi;
        int b = seg[i].se;
        if (dsu.same(a, b)) continue;

        bool useful = false;
        for (int x = a; x < b; x++) {
            if (!covered[x]) {
                useful = true;
                break;
            }
        }
        if (!useful) continue;

        dsu.merge(a, b);
        for (int x = a; x < b; x++) {
            covered[x] = 1;
        }
        ans.pb(i + 1);
    }

    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
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
