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

struct Tag {
    ll v = 1;
    void operator+=(const Tag &t) {
        v = (v * t.v) % MOD;
    }
};

struct Info {
    ll val = 0;
    Info operator+(const Info &o) const {
        Info res;
        res.val = (val + o.val) % MOD;
        return res;
    }
    void operator+=(const Tag &t) {
        val = (val * t.v) % MOD;
    }
};

struct SegTree {
    vector<Info> info;
    vector<Tag> tag;
    ll n;

    explicit SegTree(ll n_) : n(n_), info(n_ * 4 + 5), tag(n_ * 4 + 5) {}

    void apply(ll x, const Tag &v) {
        if (v.v != 1) {
            info[x] += v;
            tag[x] += v;
        }
    }

    void push_down(ll x) {
        if (tag[x].v != 1) {
            apply(x * 2, tag[x]);
            apply(x * 2 + 1, tag[x]);
            tag[x] = {};
        }
    }

    void pull_up(ll x) {
        info[x] = info[x * 2] + info[x * 2 + 1];
    }

    void update(ll x, ll l, ll r, ll lq, ll rq, const Tag &v) {
        if (lq <= l && rq >= r) {
            apply(x, v);
            return;
        }
        if (lq > r || rq < l) return;

        push_down(x);
        ll mid = l + (r - l) / 2;
        update(x * 2, l, mid, lq, rq, v);
        update(x * 2 + 1, mid + 1, r, lq, rq, v);
        pull_up(x);
    }
    void update(ll lq, ll rq, const Tag &v) {
        if (lq <= rq) update(1, 1, n, lq, rq, v);
    }

    void modify(ll x, ll l, ll r, ll pos, const Info &v) {
        if (l == r) {
            info[x] = v;
            return;
        }
        push_down(x);
        ll mid = l + (r - l) / 2;
        if (pos <= mid) modify(x * 2, l, mid, pos, v);
        else modify(x * 2 + 1, mid + 1, r, pos, v);
        pull_up(x);
    }
    void modify(ll pos, const Info &v) {
        modify(1, 1, n, pos, v);
    }

    Info ask(ll x, ll l, ll r, ll lq, ll rq) {
        if (lq > r || rq < l) return Info{};
        if (lq <= l && rq >= r) {
            return info[x];
        }
        push_down(x);
        ll mid = l + (r - l) / 2;
        return ask(x * 2, l, mid, lq, rq) + ask(x * 2 + 1, mid + 1, r, lq, rq);
    }
    Info ask(ll lq, ll rq) {
        return ask(1, 1, n, lq, rq);
    }
};

ll ksm(ll a, ll b) {
    ll res = 1; a %= MOD;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}
ll inv(ll n) {
    return ksm(n, MOD - 2);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }

    vector<int> lh, rh;
    int mxl = 0;
    for (int x : a) {
        if (x > mxl) {
            lh.pb(x);
            mxl = x;
        }
    }
    int mxr = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] > mxr) {
            rh.pb(a[i]);
            mxr = a[i];
        }
    }

    if (lh.empty() || rh.empty() || lh.back() != mx || rh.back() != mx) {
        cout << 0 << "\n";
        return;
    }

    vector<int> L = lh;
    L.pop_back();
    vector<int> R = rh;
    R.pop_back();

    auto calc = [&](const vector<int>& arr, const vector<int>& h) {
        int k = h.size();
        vector<ll> res(n, 0);
        map<int, int> mp;
        for (int i = 0; i < k; ++i) mp[h[i]] = i + 1;

        SegTree st(k + 2);
        st.modify(1, {1});

        for (int i = 0; i < n; ++i) {
            if (arr[i] == mx) res[i] = st.ask(k + 1, k + 1).val;
            if (arr[i] >= mx) continue;

            int v = arr[i];

            auto it = lower_bound(all(h), v);
            int idx = distance(h.begin(), it) + 1;
            st.update(idx + 1, k + 1, {2});

            if (mp.count(v)) {
                int j = mp[v];
                ll prev = st.ask(j, j).val;
                ll cur = st.ask(j + 1, j + 1).val;
                st.modify(j + 1, {(cur + prev) % MOD});
            }
        }
        return res;
    };

    vector<ll> cntL = calc(a, L);

    reverse(all(a));
    vector<ll> cntRr = calc(a, R);
    vector<ll> cntR(n);
    for (int i = 0; i < n; ++i) cntR[i] = cntRr[n - 1 - i];
    reverse(all(a));

    vector<int> pos;
    for (int i = 0; i < n; ++i) {
        if (a[i] == mx) pos.pb(i);
    }

    if (pos.empty()) {
        cout << (L.empty() && R.empty() ? 1 : 0) << "\n";
        return;
    }

    vector<int> less(n + 1, 0);
    for (int i = 0; i < n; ++i) less[i + 1] = less[i] + (a[i] < mx);

    vector<ll> p2(n + 1), ip2(n + 1);
    p2[0] = ip2[0] = 1;
    ll inv2 = inv(2);
    for (int i = 1; i <= n; ++i) {
        p2[i] = (p2[i - 1] * 2) % MOD;
        ip2[i] = (ip2[i - 1] * inv2) % MOD;
    }

    vector<ll> waysL(pos.size());
    ll S = 0;
    for (size_t i = 0; i < pos.size(); ++i) {
        ll cur = (cntL[pos[i]] + S * p2[less[pos[i]]]) % MOD;
        waysL[i] = cur;
        S = (S + cur * ip2[less[pos[i]]]) % MOD;
    }

    ll ans = 0;
    for (size_t i = 0; i < pos.size(); ++i) {
        ans = (ans + waysL[i] * cntR[pos[i]]) % MOD;
    }

    cout << (ans + MOD) % MOD << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}