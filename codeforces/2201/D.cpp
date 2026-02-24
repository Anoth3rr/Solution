// Problem: D. Binary Not Search and Queries
// Contest: Codeforces - Codeforces Round 1082 (Div. 1)
// URL: https://codeforces.com/contest/2201/problem/D
// Memory Limit: 512 MB
// Time Limit: 4000 ms
// By: Anoth3r

#include <bits/stdc++.h>
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define endl "\n"
using namespace std;

using ll = long long;
using ld = long double;
using ui = unsigned;
using ull = unsigned long long;
using i128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<ll, ll, ll>;

template <class Int = ll>
struct Tag {
    Int v = 0;
    void operator+=(const Tag<Int> &o) {
        v += o.v;
    }
    bool check() {
        return v != 0;
    }
};

template <class Int = ll>
struct Info {
    Int mx = -1;
    int llen, rlen;
    int l, r, siz;
    Int ans;
    Info operator+(const Info<Int> &o) const {
        if (siz == 0)
            return o;
        if (o.siz == 0)
            return *this;

        Info res;
        res.l = l;
        res.r = o.r;
        res.siz = siz + o.siz;
        res.mx = max(mx, o.mx);

        if (mx > o.mx) {
            res.llen = llen;
            res.rlen = 0;
            res.ans = ans;
        } else if (mx < o.mx) {
            res.llen = 0;
            res.rlen = o.rlen;
            res.ans = o.ans;
        } else {
            res.llen = llen;
            if (llen == siz)
                res.llen += o.llen;

            res.rlen = o.rlen;
            if (o.rlen == o.siz)
                res.rlen += rlen;

            res.ans = ans + o.ans;
            ll mid = 1LL * rlen + o.llen;
            res.ans += mid * (mid + 1) / 2 - 1LL * rlen * (rlen + 1) / 2 - 1LL * o.llen * (o.llen + 1) / 2;
        }
        return res;
    }
    void operator+=(const Tag<Int> &o) {
        mx += o.v;
    }
    bool check() {
        return l != r;
    }
};

template <class Int = ll>
class SegTree {
  private:
    vector<Info<Int>> info;
    vector<Tag<Int>> tag;
    int n;

    int ls(int x) { return x << 1; }
    int rs(int x) { return x << 1 | 1; }

    void print(int x, int l, int r) {
        cout << x << ":[" << l << "," << r << "],mx:" << info[x].mx << ",tag:" << tag[x].v << "\n";
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        print(ls(x), l, mid);
        print(rs(x), mid + 1, r);
    }

    template <class Array>
    void build(int x, int l, int r, Array &data) {
        if (l == r) {
            info[x].l = l;
            info[x].r = r;
            info[x].mx = data[l];
            info[x].siz = 1;
            info[x].llen = 1;
            info[x].rlen = 1;
            info[x].ans = 1;
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

    void modify(int x, int l, int r, int pos, Int v) {
        if (r < pos || l > pos)
            return;
        if (l == r && l == pos) {
            info[x].mx = v;
            return;
        }
        int mid = (l + r) >> 1;
        modify(ls(x), l, mid, pos, v);
        modify(rs(x), mid + 1, r, pos, v);
        info[x] = info[ls(x)] + info[rs(x)];
    }

    Info<Int> ask(int x, int l, int r, int lq, int rq) {
        if (rq < l || lq > r)
            return {Info<Int>()};
        if (lq <= l && r <= rq)
            return info[x];
        push_down(x);
        int mid = (l + r) >> 1;
        auto ans = ask(ls(x), l, mid, lq, rq) + ask(rs(x), mid + 1, r, lq, rq);
        return ans;
    }

  public:
    SegTree(int n_) : n(n_), info(4 * n_ + 1), tag(4 * n_ + 1) {}

    void print() {
        print(1, 1, n);
    }

    template <class Array>
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
    int n, q;
    cin >> n >> q;

    vector<int> V(n + 1, -1), a(n + 1);
    vector<set<int>> pos(n + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]].insert(i);
    }

    for (int i = 1; i <= n; ++i) {
        if (!pos[i].empty()) {
            int L = *pos[i].begin();
            int R = *pos[i].rbegin();
            V[L] = R - L;
        }
    }

    SegTree<int> st(n);
    st.build(V);

    for (int j = 0; j < q; ++j) {
        int idx, nv;
        cin >> idx >> nv;
        int ov = a[idx];

        if (ov != nv) {
            int lo = *pos[ov].begin();
            st.modify(lo, -1);
            pos[ov].erase(idx);
            if (!pos[ov].empty()) {
                int ln = *pos[ov].begin();
                int rn = *pos[ov].rbegin();
                st.modify(ln, rn - ln);
            }

            if (!pos[nv].empty()) {
                int lc = *pos[nv].begin();
                st.modify(lc, -1);
            }
            pos[nv].insert(idx);
            int ln2 = *pos[nv].begin();
            int rn2 = *pos[nv].rbegin();
            st.modify(ln2, rn2 - ln2);

            a[idx] = nv;
        }

        Info<int> res = st.ask(1, n);
        if (res.mx <= 0) {
            cout << "0 0" << endl;
        } else {
            cout << res.mx << " " << res.ans << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    cin >> t;
    cout << fixed << setprecision(15);
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}