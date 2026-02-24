// Problem: BenzenE
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120563/I
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

template <class T>
struct LB {
    using ull = unsigned long long;
    static constexpr int BASE = sizeof(T) * 8 - 1;
    vector<T> d, p;
    int cnt, flag;
    vector<ull> mask;
    vector<int> rep;

    LB() {
        d.assign(BASE + 1, 0);
        p.assign(BASE + 1, 0);
        mask.assign(BASE + 1, 0);
        cnt = flag = 0;
    }
    bool insert(T val, int idx) {
        ull cur = 0;
        for (int i = BASE - 1; i >= 0; i--) {
            if (val & (1ll << i)) {
                if (!d[i]) {
                    d[i] = val;
                    mask[i] = cur | (1ull << rep.size());
                    rep.push_back(idx);
                    return true;
                }
                val ^= d[i];
                cur ^= mask[i];
            }
        }
        flag = 1;
        return false;
    }
    pair<bool, ull> check(T val) {
        ull res = 0;
        for (int i = BASE - 1; i >= 0; --i) {
            if (val & (1ll << i)) {
                if (!d[i])
                    return {false, 0ull};
                val ^= d[i];
                res ^= mask[i];
            }
        }
        return {true, res};
    }
    ll ask_max() {
        ll res = 0;
        for (int i = BASE - 1; i >= 0; i--) {
            if ((res ^ d[i]) > res)
                res ^= d[i];
        }
        return res;
    }
    ll ask_min() {
        if (flag)
            return 0;
        for (int i = 0; i <= BASE - 1; i++) {
            if (d[i])
                return d[i];
        }
    }
    void rebuild() {
        for (int i = BASE - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (d[i] & (1ll << j))
                    d[i] ^= d[j];
            }
        }
        for (int i = 0; i <= BASE - 1; i++) {
            if (d[i])
                p[cnt++] = d[i];
        }
    }
    ll kthquery(ll k) {
        if (flag)
            k--;
        if (!k)
            return 0;
        ll res = 0;
        if (k >= (1ll << cnt))
            return -1;
        for (int i = BASE - 1; i >= 0; i--) {
            if (k & (1LL << i))
                res ^= p[i];
        }
        return res;
    }
    void Merge(const LB &b) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (b.d[i]) {
                insert(b.d[i]);
            }
        }
    }
    vector<int> choose(ull mask) {
        vector<int> res;
        for (int i = 0; i < rep.size(); ++i) {
            if (mask & (1ull << i)) {
                res.pb(rep[i]);
            }
        }
        return res;
    }
};

void init() {
}

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n), b(n), x(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        cin >> b[i];
    ll S = 0;
    for (int i = 0; i < n; ++i)
        S ^= a[i];
    for (int i = 0; i < n; ++i)
        x[i] = a[i] ^ b[i];

    LB<ll> lb;
    for (int i = 0; i < n; ++i) {
        if (x[i] != 0)
            lb.insert(x[i], i);
    }

    auto [f, mask] = lb.check(S);
    if (!f) {
        cout << -1 << endl;
        return;
    }
    vector<int> vis(n);
    for (auto v : lb.choose(mask))
        vis[v] = 1;
    for (int i = 0; i < n; ++i) {
        cout << (vis[i] ? b[i] : a[i]) << " ";
    }
    cout << endl;
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