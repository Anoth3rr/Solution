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

void init() {

}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<PII> segs(q);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        segs[i] = {l, r};
    }

    vector<int> st(n + 2, 0);
    for (auto [u, v] : segs) {
        st[u] = max(st[u], v);
    }
    vector<int> g(n + 2, 0);
    for (int i = 1; i <= n; ++i) {
        g[i] = max(g[i - 1], st[i]);
    }

    vector<int> memo1(n + 2, -1), memo2(n + 2, -1);

    auto ask = [&](int l, int r) -> int {
        if (l < 1) l = 1;
        if (r > n) r = n;
        if (l > r) return 0;
        cout << "? " << l << " " << r << endl;
        int ans;
        cin >> ans;
        return ans;
    };

    function<int(int)> getA = [&](int L) -> int {
        if (L < 1 || L > n) return 0;
        int &ref = memo1[L];
        if (ref != -1) return ref;
        ref = ask(L, n);
        return ref;
    };
    function<int(int)> getB = [&](int R) -> int {
        if (R < 1) return 0;
        if (R > n) R = n;
        int &ref = memo2[R];
        if (ref != -1) return ref;
        ref = ask(1, R);
        return ref;
    };

    auto getF = [&](int L) -> int {
        if (L < 1 || L > n) return 0;
        int a = getA(L);
        int h = (g[L] >= 1 ? getB(g[L]) : 0);
        return min(a, h);
    };

    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        int a = getA(mid);
        int h = (g[mid] >= 1 ? getB(g[mid]) : 0);
        if (a <= h) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    int L0 = lo;

    int cand1 = getF(L0);
    int cand2 = (L0 > 1 ? getF(L0 - 1) : 0);
    int ans = max(cand1, cand2);

    cout << "! " << ans << endl;
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