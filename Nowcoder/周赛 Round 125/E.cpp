// Problem: 小苯的数组操作
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126418/E
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// By: Anoth3r

#include <bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define endl "\n"
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using i128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<ll, ll, ll>;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ld eps = 1e-10;

template <class Int> struct Tag {
    Int add = 0;
    Int set = 0;
    bool f = false;

    static Tag make_add(Int v) { return {v, 0, false}; }
    static Tag make_set(Int v) { return {0, v, true}; }

    void operator+=(const Tag<Int> &o) {
        if (o.f) {
            f = true;
            set = o.set;
            add = 0;
        } else {
            if (f) {
                set += o.add;
            } else {
                add += o.add;
            }
        }
    }

    bool check() { return f || add != 0; }
};

template <class Int> struct Info {
    Int sum = 0;
    Int mx = 0;
    Int mn = 0;
    int l = 0, r = 0;

    void set(int pos, Int val) {
        l = r = pos;
        sum = val;
        mx = val;
        mn = val;
    }

    Info operator+(const Info<Int> &o) const {
        if (l == 0)
            return o;
        if (o.l == 0)
            return *this;

        Info res;
        res.l = l;
        res.r = o.r;
        res.sum = sum + o.sum;
        res.mx = max(mx, o.mx);
        res.mn = min(mn, o.mn);
        return res;
    }

    void operator+=(const Tag<Int> &o) {
        if (o.f) {
            sum = o.set * (r - l + 1);
            mx = o.set;
            mn = o.set;
        } else {
            sum += o.add * (r - l + 1);
            mx += o.add;
            mn += o.add;
        }
    }

    bool check() { return l != r; }
};

template <class Int> class SegTree {
  private:
    vector<Info<Int>> info;
    vector<Tag<Int>> tag;
    int n;

    int ls(int x) { return x << 1; }
    int rs(int x) { return x << 1 | 1; }

    void print(int x, int l, int r) {
        if (l == 0)
            return;
        cout << x << ":[" << l << "," << r << "] sum:" << info[x].sum
             << " max:" << info[x].mx << " tag_add:" << tag[x].add
             << " tag_set:" << tag[x].set << " f:" << tag[x].f << "\n";
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        print(ls(x), l, mid);
        print(rs(x), mid + 1, r);
    }

    template <class Array> void build(int x, int l, int r, Array &data) {
        if (l == r) {
            info[x].set(l, data[l]);
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(x), l, mid, data);
        build(rs(x), mid + 1, r, data);
        info[x] = info[ls(x)] + info[rs(x)];
    }

    void push_down(int x) {
        if (tag[x].check()) {
            info[ls(x)] += tag[x];
            info[rs(x)] += tag[x];
            tag[ls(x)] += tag[x];
            tag[rs(x)] += tag[x];
            tag[x] = {0, 0, false};
        }
    }

    void update(int x, int l, int r, int lq, int rq, Tag<Int> v) {
        if (rq < l || lq > r)
            return;
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

    Info<Int> ask(int x, int l, int r, int lq, int rq) {
        if (rq < l || lq > r)
            return Info<Int>();
        if (lq <= l && r <= rq)
            return info[x];
        push_down(x);
        int mid = (l + r) >> 1;
        return ask(ls(x), l, mid, lq, rq) + ask(rs(x), mid + 1, r, lq, rq);
    }

  public:
    SegTree(int n_) : n(n_), info(4 * n_ + 1), tag(4 * n_ + 1) {}

    template <class Array> void build(Array &data) { build(1, 1, n, data); }

    void add(int l, int r, Int v) {
        update(1, 1, n, l, r, Tag<Int>::make_add(v));
    }

    void set(int l, int r, Int v) {
        update(1, 1, n, l, r, Tag<Int>::make_set(v));
    }

    void modify(int pos, Int v) { set(pos, pos, v); }

    Int getSum(int l, int r) { return ask(1, 1, n, l, r).sum; }

    Int getMax(int l, int r) { return ask(1, 1, n, l, r).mx; }

    Int getMin(int l, int r) { return ask(1, 1, n, l, r).mn; }

    Info<Int> query_info(int l, int r) { return ask(1, 1, n, l, r); }

    void print() { print(1, 1, n); }
};

void init() {}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    SegTree<int> seg(n);
    seg.build(a);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i;
            cin >> i;
            int mn = seg.getMin(1, i);
            seg.set(1, i, mn);
        } else if (op == 2) {
            int i;
            cin >> i;
            int mn = seg.getMin(i, n);
            seg.set(i, n, mn);
        } else {
            cout << seg.getSum(1, n) << endl;
        }
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