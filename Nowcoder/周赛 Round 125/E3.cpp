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

class Block {
  private:
    int n;
    int B;
    int num_B;

    vector<ll> a;

    vector<int> st, ed;
    vector<int> bel;
    vector<ll> mn;
    vector<ll> sum;
    vector<ll> lazy;

    ll tot;

    void push_down(int b) {
        if (lazy[b] == 0)
            return;
        for (int i = st[b]; i <= ed[b]; ++i) {
            a[i] = lazy[b];
        }
        lazy[b] = 0;
    }

    void rebuild(int b) {
        ll cur_min = INF;
        ll cur_sum = 0;
        for (int i = st[b]; i <= ed[b]; ++i) {
            cur_min = min(cur_min, a[i]);
            cur_sum += a[i];
        }
        mn[b] = cur_min;

        tot -= sum[b];
        sum[b] = cur_sum;
        tot += sum[b];
    }

  public:
    Block(int _n, const vector<int> &input_a) : n(_n), tot(0) {
        a.resize(n + 1);
        for (int i = 1; i <= n; ++i)
            a[i] = input_a[i];

        B = sqrt(n);
        num_B = (n + B - 1) / B;

        st.resize(num_B + 1);
        ed.resize(num_B + 1);
        bel.resize(n + 1);
        mn.assign(num_B + 1, INF);
        sum.assign(num_B + 1, 0);
        lazy.assign(num_B + 1, 0);

        for (int i = 1; i <= num_B; ++i) {
            st[i] = (i - 1) * B + 1;
            ed[i] = min(i * B, n);
            for (int j = st[i]; j <= ed[i]; ++j) {
                bel[j] = i;
                mn[i] = min(mn[i], a[j]);
                sum[i] += a[j];
            }
            tot += sum[i];
        }
    }

    ll getMin(int l, int r) {
        int bl = bel[l], br = bel[r];
        ll res = INF;

        if (bl == br) {
            push_down(bl);
            for (int i = l; i <= r; ++i)
                res = min(res, a[i]);
        } else {
            push_down(bl);
            for (int i = l; i <= ed[bl]; ++i)
                res = min(res, a[i]);

            for (int b = bl + 1; b < br; ++b)
                res = min(res, mn[b]);

            push_down(br);
            for (int i = st[br]; i <= r; ++i)
                res = min(res, a[i]);
        }
        return res;
    }

    void set(int l, int r, ll val) {
        int bl = bel[l], br = bel[r];

        if (bl == br) {
            push_down(bl);
            for (int i = l; i <= r; ++i)
                a[i] = val;
            rebuild(bl);
        } else {
            push_down(bl);
            for (int i = l; i <= ed[bl]; ++i)
                a[i] = val;
            rebuild(bl);

            for (int b = bl + 1; b < br; ++b) {
                lazy[b] = val;
                mn[b] = val;

                tot -= sum[b];
                sum[b] = val * (ed[b] - st[b] + 1);
                tot += sum[b];
            }

            push_down(br);
            for (int i = st[br]; i <= r; ++i)
                a[i] = val;
            rebuild(br);
        }
    }

    ll getSum() { return tot; }
};

void init() {}

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    Block block(n, a);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i;
            cin >> i;
            ll mn = block.getMin(1, i);
            block.set(1, i, mn);
        } else if (op == 2) {
            int i;
            cin >> i;
            ll mn = block.getMin(i, n);
            block.set(i, n, mn);
        } else {
            cout << block.getSum() << endl;
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