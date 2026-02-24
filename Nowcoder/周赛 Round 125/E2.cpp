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

template <class Int> struct Node {
    int l, r;
    mutable Int v;
    bool operator<(const Node &o) const { return l < o.l; }
};

template <class Int> struct ODT {
    set<Node<Int>> s;
    Int sum = 0;
    int n = 0;

    ODT(int n_) : n(n_) {}

    template <class Array> void build(Array &data) {
        s.clear();
        sum = 0;
        for (int i = 1; i <= n;) {
            int j = i;
            while (j <= n && data[j] == data[i])
                j++;
            s.insert({i, j - 1, data[i]});
            sum += data[i] * (j - i);
            i = j;
        }
    }

    auto split(int pos) {
        if (pos > n)
            return s.end();
        auto it = s.lower_bound({pos, 0, Int()});
        if (it != s.end() && it->l == pos)
            return it;
        if (it == s.begin())
            return s.end();
        --it;
        int l = it->l, r = it->r;
        Int v = it->v;
        s.erase(it);
        s.insert({l, pos - 1, v});
        return s.insert({pos, r, v}).first;
    }

    void setMax(int l, int r) {
        if (l > r)
            return;

        auto itr = split(r + 1);
        auto itl = split(l);

        Int mx = numeric_limits<Int>::min();

        for (auto it = itl; it != itr;) {
            mx = max(mx, it->v);
            sum -= it->v * (it->r - it->l + 1);
            it = s.erase(it);
        }

        s.insert({l, r, mx});
        sum += mx * (r - l + 1);
    }

    void setMin(int l, int r) {
        if (l > r)
            return;

        auto itr = split(r + 1);
        auto itl = split(l);

        Int mn = numeric_limits<Int>::max();

        for (auto it = itl; it != itr;) {
            mn = min(mn, it->v);
            sum -= it->v * (it->r - it->l + 1);
            it = s.erase(it);
        }

        s.insert({l, r, mn});
        sum += mn * (r - l + 1);
    }
};

void init() {}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    ODT<ll> tree(n);
    tree.build(a);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i;
            cin >> i;
            tree.setMin(1, i);
        } else if (op == 2) {
            int i;
            cin >> i;
            tree.setMin(i, n);
        } else {
            cout << tree.sum << endl;
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