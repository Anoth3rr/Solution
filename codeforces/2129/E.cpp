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
const int N = 150005;
const int VAL = 1 << 18;
const int S = 400;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

struct Q {
    int l, r, k, id;
};

vector<int> g[N], g_heavy[N];
int f[N];
int B;
bool is_heavy[N];
int heavy_id[N], total_heavy;
int correction[N];
int val_heavy[1 << 10];
vector<int> heavy_adj_mask;

struct BIT {
    int n;
    vector<int> tree;
    void init(int sz) { n = sz; tree.assign(n + 1, 0); }
    void add(int x, int v) { for (int i = x + 1; i <= n; i += i & -i) tree[i] += v; }
    int sum(int x) { int res = 0; for (int i = x; i > 0; i -= i & -i) res += tree[i]; return res; }
} bit;

void update_val(int u, int v) {
    if (is_heavy[u]) {
        f[u] ^= v;
    } else {
        bit.add(f[u], -1);
        f[u] ^= v;
        bit.add(f[u], 1);
    }
}

void add(int u) {
    if (is_heavy[u]) {
        correction[heavy_id[u]] = u;
    } else {
        int total_heavy_xor = 0;
        for (int h_idx : g_heavy[u]) {
            total_heavy_xor ^= correction[h_idx];
        }
        f[u] = total_heavy_xor;
        for (int v : g[u]) {
            if (v < u) {
                if (correction[0] <= v && v <= correction[1]) {
                    update_val(v, u);
                    f[u] ^= v;
                }
            }
        }
        bit.add(f[u], 1);
    }
}

void rem(int u) {
    if (is_heavy[u]) {
        correction[heavy_id[u]] = 0;
    } else {
        bit.add(f[u], -1);
        for (int v : g[u]) {
            if (v < u) {
                if (correction[0] <= v && v < correction[1]) {
                    update_val(v, u);
                }
            }
        }
        f[u] = 0;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        g[i].clear();
        g_heavy[i].clear();
        is_heavy[i] = false;
        heavy_id[i] = 0;
    }
    total_heavy = 0;

    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        g[u].pb(v); g[v].pb(u);
    }

    for (int i = 1; i <= n; ++i) {
        if (g[i].size() > S) {
            is_heavy[i] = true;
            heavy_id[i] = total_heavy++;
        }
    }

    heavy_adj_mask.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        for (int v : g[i]) {
            if (is_heavy[v]) {
                g_heavy[i].pb(heavy_id[v]);
                heavy_adj_mask[i] |= (1 << heavy_id[v]);
            }
        }
    }

    int q_cnt;
    cin >> q_cnt;
    vector<Q> qs(q_cnt);
    vector<int> res(q_cnt);
    for (int i = 0; i < q_cnt; ++i) {
        cin >> qs[i].l >> qs[i].r >> qs[i].k;
        qs[i].id = i;
    }

    B = (n > 0) ? n / max(1, (int)sqrt(q_cnt)) : 1;
    if (B == 0) B = 1;
    sort(all(qs), [&](const Q & a, const Q & b) {
        int ba = a.l / B, bb = b.l / B;
        if (ba != bb) return ba < bb;
        return (ba & 1) ? (a.r < b.r) : (a.r > b.r);
    });

    bit.init(VAL);
    fill(f + 1, f + n + 1, 0);
    fill(correction, correction + total_heavy, 0);

    int cl = 1, cr = 0;
    for (auto& q : qs) {
        correction[0] = q.l, correction[1] = q.r;
        while (cl > q.l) { --cl; add(cl); }
        while (cr < q.r) { ++cr; add(cr); }
        while (cl < q.l) { rem(cl); cl++; }
        while (cr > q.r) { rem(cr); cr--; }

        int total_heavy_xor_mask = 0;
        for (int i = 0; i < total_heavy; ++i) {
            if (correction[i]) total_heavy_xor_mask |= (1 << i);
        }

        val_heavy[0] = 0;
        for (int i = 1; i < (1 << total_heavy); ++i) {
            int lsb_idx = __builtin_ctz(i);
            val_heavy[i] = val_heavy[i ^ (1 << lsb_idx)] ^ correction[lsb_idx];
        }

        int l_ans = 0, r_ans = VAL - 1, ans = 0;
        while (l_ans <= r_ans) {
            int mid = l_ans + (r_ans - l_ans) / 2;
            int count_less = 0;
            for (int i = 0; i < (1 << total_heavy); ++i) {
                if ((i & total_heavy_xor_mask) == i) {
                    count_less += bit.sum((mid ^ val_heavy[i]) + 1);
                }
            }
            for (int i = 1; i <= n; ++i) {
                if (is_heavy[i] && i >= q.l && i <= q.r) {
                    if ((f[i] ^ val_heavy[heavy_adj_mask[i] & total_heavy_xor_mask]) <= mid) {
                        count_less++;
                    }
                }
            }

            if (count_less >= q.k) {
                ans = mid;
                r_ans = mid - 1;
            } else {
                l_ans = mid + 1;
            }
        }
        res[q.id] = ans;
    }

    for (int i = 0; i < q_cnt; ++i) {
        cout << res[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}