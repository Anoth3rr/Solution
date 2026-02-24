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
constexpr int maxn = 100;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

vector<int> primes, spf(maxn + 1);
int P;

void init() {
    for (int i = 2; i <= maxn; ++i) {
        if (!spf[i]) primes.push_back(i), spf[i] = i;
        for (int j = 0; primes[j]*i <= maxn; ++j) {
            int m = primes[j] * i;
            spf[m] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
    P = primes.size();
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> mask(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        int m = 0;
        for (int i = 0; i < P; ++i) {
            int v = primes[i], cnt = 0;
            while (x % v == 0) {
                x /= v;
                cnt ^= 1;
            }
            if (cnt) m |= (1 << i);
        }
        mask[i] = m;
    }

    vector<vector<PII>> qs(n + 1);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        qs[r].pb({l, i});
    }

    vector<string> ans(q);
    vector<int> basis(P), pos(P);

    auto insert = [&](int x, int idx) {
        int cur = x;
        int cpos = idx;
        for (int b = P - 1; b >= 0 && cur; --b) {
            if (!((cur >> b) & 1)) continue;
            if (basis[b] == 0) {
                basis[b] = cur;
                pos[b] = cpos;
                return;
            }
            if (pos[b] < cpos) {
                swap(pos[b], cpos);
                swap(basis[b], cur);
            }
            cur ^= basis[b];
        }
    };

    for (int r = 1; r <= n; ++r) {
        insert(mask[r], r);
        for (auto [l, idx] : qs[r]) {
            int cnt = 0;
            for (int b = 0; b < P; ++b) if (pos[b] >= l) ++cnt;
            int total = r - l + 1;
            ans[idx] = (cnt < total) ? "Yes" : "No";
        }
    }

    for (int i = 0; i < q; ++i) cout << ans[i] << "\n";
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