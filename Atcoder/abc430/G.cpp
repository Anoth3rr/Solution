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
typedef pair<ll, ll> Pll;
typedef tuple<ll, ll, ll> Tlll;
typedef __gnu_pbds::tree<Pll, __gnu_pbds::null_type, less<Pll>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;
// typedef __gnu_pbds::tree<ll, __gnu_pbds::null_type, less<ll>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ld PI = acos(-1.0);
constexpr ld eps = 1e-10;
constexpr int maxn = 60;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

template<class Int>
struct Tag {
    Int v = 0;
    void operator+=(const Tag<Int> &o) {
        v += o.v;
    }
    bool check() {
        return v != 0;
    }
};

template<class Int>
struct Info {
    Int val = 0;
    int cnt = 1;
    int l = 0, r = 0;

    Info() { val = 0; cnt = 1; l = r = 0; }

    Info(int) { val = -inf; cnt = 0; l = r = 0; }

    Info operator+(const Info<Int> &o) const {
        Info res;
        res.l = l;
        res.r = o.r;
        if (val > o.val) {
            res.val = val;
            res.cnt = cnt;
        } else if (val < o.val) {
            res.val = o.val;
            res.cnt = o.cnt;
        } else {
            res.val = val;
            res.cnt = cnt + o.cnt;
        }
        return res;
    }
    void operator+=(const Tag<Int> &o) {
        val += o.v;
    }
    bool check() {
        return l != r;
    }
};

template<class Int>
class SegTree {
private:
    vector<Info<Int>> info;
    vector<Tag<Int>> tag;
    int n;

    int ls(int x) {return x << 1;}
    int rs(int x) {return x << 1 | 1;}

    void print(int x, int l, int r) {
        cout << x << ":[" << l << "," << r << "],val:" << info[x].val << ",cnt:" << info[x].cnt << ",tag:" << tag[x].v << "\n";
        if (l == r) return;
        int mid = l + r >> 1;
        print(ls(x), l, mid);
        print(rs(x), mid + 1, r);
    }

    template<class Array>
    void build(int x, int l, int r, Array &data) {
        info[x].l = l;
        info[x].r = r;
        if (l == r) {
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
        push_down(x);
        modify(ls(x), l, mid, pos, v);
        modify(rs(x), mid + 1, r, pos, v);
        info[x] = info[ls(x)] + info[rs(x)];
    }

    Info<Int> ask(int x, int l, int r, int lq, int rq) {
        if (rq < l || lq > r) return {0};
        if (lq <= l && r <= rq) return info[x];
        push_down(x);
        int mid = (l + r) >> 1;
        auto left = ask(ls(x), l, mid, lq, rq);
        auto right = ask(rs(x), mid + 1, r, lq, rq);
        if (left.cnt == 0) return right;
        if (right.cnt == 0) return left;
        return left + right;
    }
public:
    SegTree(int n_): n(n_), info(4 * n_ + 1), tag(4 * n_ + 1) {}

    void printTree() {
        print(1, 1, n);
    }

    template<class Array>
    void build(Array &data) {
        build(1, 1, n, data);
    }

    void update(int l, int r, Tag<Int> v) {
        if (l > r) return;
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
    int n, q;
    cin >> n >> q;

    SegTree<int> seg(n);
    vector<int> init(n + 1, 0);
    seg.build(init);

    vector<set<PII>> ones(maxn + 1);

    for (int i = 0; i < q; ++i) {
        int op; cin >> op;
        if (op == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            if (l > r) continue;
            seg.update(l, r, Tag<int> {1});
            auto &S = ones[x];
            auto it = S.lower_bound({l + 1, -inf});
            if (it != S.begin()) {
                --it;
                if (it->se < l) ++it;
            }
            int nl = l, nr = r;
            vector<PII> del;
            while (it != S.end() && it->fi <= r) {
                int a = it->fi, b = it->se;
                int ovl = max(a, l), ovr = min(b, r);
                if (ovl <= ovr) seg.update(ovl, ovr, Tag<int> { -1});
                nl = min(nl, a);
                nr = max(nr, b);
                del.pb(*it);
                ++it;
            }
            for (auto &p : del) S.erase(p);
            S.insert({nl, nr});
        }
        else if (op == 2) {
            int l, r, x; cin >> l >> r >> x;
            if (l > r) continue;
            auto &S = ones[x];
            auto it = S.lower_bound({l + 1, -inf});
            if (it != S.begin()) {
                --it;
                if (it->se < l) ++it;
            }
            vector<PII> del;
            vector<PII> add;
            while (it != S.end() && it->fi <= r) {
                int a = it->fi, b = it->se;
                int ovl = max(a, l), ovr = min(b, r);
                if (ovl <= ovr) seg.update(ovl, ovr, Tag<int> { -1});
                del.pb(*it);
                if (a < ovl) add.pb({a, ovl - 1});
                if (ovr < b) add.pb({ovr + 1, b});
                ++it;
            }
            for (auto &p : del) S.erase(p);
            for (auto &p : add) S.insert(p);
        }
        else if (op == 3) {
            int l, r;
            cin >> l >> r;
            auto res = seg.ask(l, r);
            cout << res.val << " " << res.cnt << "\n";
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
