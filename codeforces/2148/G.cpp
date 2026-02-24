//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define _0x0_ cin
#define _0w0_ cout
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
constexpr int maxn = 200000;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

vector<vector<int>> divi(maxn + 10);
int cnt[maxn + 10];
int freq[maxn + 10];

class Node {
public:
    ll sum;
    ll add;
    Node() {
        sum = 0;
        add = 0;
    }
};
class SegTree {
public:
    vector<Node> tree;
    ll n_;
    SegTree(ll n = 0) {
        n_ = n;
        tree.resize(4 * n + 4);
    }
    void push_up(ll p) {
        tree[p].sum = tree[p << 1].sum + tree[p << 1 | 1].sum;
    }
    void push_down(ll p, ll l, ll r) {
        if (tree[p].add == 0) return;
        ll mid = (l + r) >> 1;
        tree[p << 1].add += tree[p].add;
        tree[p << 1].sum += tree[p].add;
        tree[p << 1 | 1].add += tree[p].add;
        tree[p << 1 | 1].sum += tree[p].add;
        tree[p].add = 0;
    }
    void build(vector<ll>&a, ll p, ll l, ll r) {
        if (l == r) {
            tree[p].sum = a[l];
            return;
        }
        ll mid = (l + r) >> 1;
        build(a, p << 1, l, mid);
        build(a, p << 1 | 1, mid + 1, r);
        push_up(p);
    }
    void init(vector<ll> &a) {
        build(a, 1, 1, n_);
    }
    void update(ll L, ll R, ll d) {
        if (L > R) return;
        update(1, 1, n_, L, R, d);
    }
    void update(ll p, ll l, ll r, ll L, ll R, ll d) {
        if (L <= l && r <= R) {
            tree[p].add += d;
            tree[p].sum += d;
            return;
        }
        push_down(p, l, r);
        ll mid = (l + r) >> 1;
        if (L <= mid) update(p << 1, l, mid, L, R, d);
        if (mid + 1 <= R) update(p << 1 | 1, mid + 1, r, L, R, d);
        push_up(p);
    }
    ll query(ll L, ll R) {
        if (L > R) return 0;
        return query(1, 1, n_, L, R);
    }
    ll query(ll p, ll l, ll r, ll L, ll R) {
        if (L <= l && r <= R) {
            return tree[p].sum;
        }
        push_down(p, l, r);
        ll mid = (l + r) >> 1;
        ll res = 0;
        if (L <= mid) res += query(p << 1, l, mid, L, R);
        if (mid + 1 <= R) res += query(p << 1 | 1, mid + 1, r, L, R);
        return res;
    }

    ll find(ll R) {
        if (R < 1) return -1;
        ll l = 1, r = R, ans = -1;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            if (query(mid, R) > 0) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }

};

void init() {
    for (int i = 1; i <= maxn; ++i) {
        for (int j = i; j <= maxn; j += i) {
            divi[j].pb(i);
        }
    }
}

void solve() {
    ll n;
    cin >> n;
    vector<int> a(n);
    vector<int> vis;

    SegTree seg(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; ++i) {
        int x = a[i - 1];
        for (int d : divi[x]) {
            if (d == 1) continue;

            int prev = cnt[d];
            if (prev == 0) {
                vis.pb(d);
            }

            if (prev > 0) {
                freq[prev]--;
                if (freq[prev] == 0) {
                    seg.update(prev, prev, 0);
                }
            }

            int cur = prev + 1;
            cnt[d] = cur;

            if (freq[cur] == 0) {
                seg.update(cur, cur, cur);
            }
            freq[cur]++;
        }

        cout << seg.query(1, i - 1) << " ";
    }
    cout << "\n";

    for (int d : vis) {
        if (cnt[d] > 0) {
            freq[cnt[d]] = 0;
            cnt[d] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    init();

    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    return 0;
}