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

template<typename Int>
struct Tag {
    Int v = 0;
    void operator+=(const Tag<Int> &o) {
        v += o.v;
    }
    bool check() {
        return v != 0;
    }
};

template<typename Int>
struct Info {
    Int val = 0;
    int l, r;
    Info operator+(const Info<Int> &o) const {
        Info res;
        res.l = l;
        res.r = o.r;
        res.val = val + o.val;
        return res;
    }
    void operator+=(const Tag<Int> &o) {
        val += o.v * (r - l + 1);
    }
    bool check() {
        return l != r;
    }
};

template<typename Int>
class SegTree {
private:
    vector<Info<Int>> info;
    vector<Tag<Int>> tag;
    int n;

    int ls(int x) {return x << 1;}
    int rs(int x) {return x << 1 | 1;}

    void print(int x, int l, int r) {
        cout << x << ":[" << l << "," << r << "],val:" << info[x].val << ",tag:" << tag[x].v << "\n";
        if (l == r) return;
        int mid = l + r >> 1;
        print(ls(x), l, mid);
        print(rs(x), mid + 1, r);
    }

    template<typename Array>
    void build(int x, int l, int r, Array &data) {
        if (l == r) {
            info[x].l = l;
            info[x].r = r;
            info[x].val = data[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(x), l, mid, data);
        build(rs(x), mid + 1, r, data);
        info[x] = info[ls(x)] + info[rs(x)];
    }

    void push_down(int x) {
        if (tag[x].check() && info[x].check()) {
            info[ls(x)] += tag[x];
            info[rs(x)] += tag[x];
            tag[ls(x)] += tag[x];
            tag[rs(x)] += tag[x];
            tag[x] = {0};
        }
    }

    void update(int x, int l, int r, int lq, int rq, Tag<Int> v) {
        if (rq < l || lq > r) return;
        if (lq <= l && r <= rq) {
            info[x] += v;
            tag[x] += v;
            return;
        }
        push_down(x);
        int mid = (l + r) >> 1;
        update(ls(x), l, mid, lq, rq, v);
        update(rs(x), mid + 1, r, lq, rq, v);
        info[x] = info[ls(x)] + info[rs(x)];
    }

    void modify(int x, int l, int r, int pos, Int v) {
        if (r < pos || l > pos) return;
        if (l == r && l == pos) {
            info[x].val = v;
            return;
        }
        int mid = (l + r) >> 1;
        modify(ls(x), l, mid, pos, v);
        modify(rs(x), mid + 1, r, pos, v);
        info[x] = info[ls(x)] + info[rs(x)];
    }

    Info<Int> ask(int x, int l, int r, int lq, int rq) {
        if (rq < l || lq > r) return {0};
        if (lq <= l && r <= rq) return info[x];
        push_down(x);
        int mid = (l + r) >> 1;
        auto ans = ask(ls(x), l, mid, lq, rq) + ask(rs(x), mid + 1, r, lq, rq);
        return ans;
    }
public:
    SegTree(int n_): n(n_), info(4 * n_ + 1), tag(4 * n_ + 1) {}

    void print() {
        print(1, 1, n);
    }

    template<typename Array>
    void build(Array &data) {
        build(1, 1, n, data);
    }

    void update(int l, int r, Tag<Int> v) {
        update(1, 1, n, l, r, v);
    }

    void modify(int pos, Int v) {
        modify(1, 1, n, pos, v);
    }

    Info<Int> ask(int l, int r) {
        return ask(1, 1, n, l, r);
    }
};

void init() {

}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    SegTree<ll> seg(n);
    seg.build(a);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            ll k;
            cin >> x >> y >> k;
            Tag cur = {k};
            seg.update(x, y, cur);
        } else {
            int x, y;
            cin >> x >> y;
            cout << seg.ask(x, y).val << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    init();

    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    return 0;
}