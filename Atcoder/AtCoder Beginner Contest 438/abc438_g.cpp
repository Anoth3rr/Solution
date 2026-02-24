// Problem: G - Sum of Min
// Contest: AtCoder - AtCoder Beginner Contest 438
// URL: https://atcoder.jp/contests/abc438/tasks/abc438_g
// Memory Limit: 1024 MB
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

template <class T> constexpr T ksm(T a, ll b) {
    T res = 1;
    while (b) {
        if (b & 1)
            res *= a;
        b >>= 1;
        a *= a;
    }
    return res;
}

template <int P> struct MInt {
    int x;
    constexpr MInt() : x() {}
    constexpr MInt(ll x) : x{norm(x % getMod())} {}
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) { Mod = Mod_; }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const { return x; }
    explicit constexpr operator int() const { return x; }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return ksm(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & { return *this *= rhs.inv(); }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr istream &operator>>(istream &is, MInt &a) {
        ll v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};

template <> int MInt<0>::Mod = 998244353;

template <int V, int P> constexpr MInt<P> CInv = MInt<P>(V).inv();

using Z = MInt<MOD>;

template <class T> T sign(const T &a) { return a == 0 ? 0 : (a < 0 ? -1 : 1); }
template <class T> T ceil(const T &a, const T &b) {
    T A = abs(a), B = abs(b);
    assert(b != 0);
    return sign(a) * sign(b) > 0 ? (A + B - 1) / B : -A / B;
}
template <class T> T exgcd(T a, T b, T &x, T &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    T d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

template <class T> T inv(T a, T m) {
    T x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}

template <class Int> struct BIT {
    vector<Int> a;
    int n;

    BIT() {}
    BIT(int n) { init(n); }

    void init(int n) {
        this->n = n;
        a.resize(n + 1);
    }

    void add(int x, Int k) {
        for (; x <= n; x += x & -x) {
            a[x] += k;
        }
    }

    void add(int x, int y, Int k) { add(x, k), add(y + 1, -k); }

    Int ask(int x) {
        Int ans = 0;
        for (; x; x -= x & -x) {
            ans += a[x];
        }
        return ans;
    }

    Int ask(int x, int y) { return ask(y) - ask(x - 1); }

    Int kth(int k) {
        Int ans = 0;
        for (int i = __lg(n); i >= 0; i--) {
            Int val = ans + (1 << i);
            if (val < n && a[val] < k) {
                k -= a[val];
                ans = val;
            }
        }
        return ans + 1;
    }
};

struct Query {
    int id, val, l, r;
    ll weight;
};

struct Event {
    int val, idx;
};

void init() {}

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n), B(m);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> B[i];

    ll g = __gcd(n, m);
    Z ans = 0;

    vector<int> X;
    vector<Query> qs;
    vector<Event> events;

    for (int r = 0; r < g; r++) {
        if (k <= r)
            break;
        ll limit = (k - 1 - r) / g + 1;

        ll n_ = n / g;
        ll m_ = m / g;

        ll fc = limit / (n_ * m_);
        ll rem = limit % (n_ * m_);

        X.resize(n_);
        for (int t = 0; t < n_; t++) {
            ll idx = ((ll)t * m_) % n_ * g + r;
            X[t] = a[idx];
        }

        qs.clear();

        if (fc > 0) {
            for (int y = 0; y < m_; y++) {
                qs.pb({-1, B[y * g + r], 0, n_ - 1, fc});
            }
        }

        if (rem > 0) {
            ll invm = inv(m_, n_);
            for (int y = 0; y < m_; y++) {
                if (rem - 1 - y < 0)
                    continue;
                ll count = (rem - 1 - y) / m_ + 1;

                int st = ((ll)y * invm) % n_;
                int end = (st + count - 1) % n_;

                if (st <= end) {
                    qs.pb({-1, B[y * g + r], st, end, 1});
                } else {
                    qs.pb({-1, B[y * g + r], st, n_ - 1, 1});
                    qs.pb({-1, B[y * g + r], 0, end, 1});
                }
            }
        }

        if (qs.empty())
            continue;

        events.resize(n_);
        for (int i = 0; i < n_; i++) {
            events[i] = {X[i], i};
        }

        sort(all(qs), [&](Query a, Query b) { return a.val < b.val; });
        sort(all(events), [&](Event a, Event b) { return a.val < b.val; });

        BIT<int> tc(n_);
        BIT<Z> ts(n_);

        int ptr = 0;
        for (auto q : qs) {
            while (ptr < n_ && events[ptr].val < q.val) {
                tc.add(events[ptr].idx + 1, 1);
                ts.add(events[ptr].idx + 1, Z(events[ptr].val));
                ptr++;
            }

            int cnt = tc.ask(q.l + 1, q.r + 1);
            Z sum = ts.ask(q.l + 1, q.r + 1);
            int len = q.r - q.l + 1;

            Z cur = sum + Z(q.val) * Z(len - cnt);
            ans += cur * Z(q.weight);
        }
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}