// Problem: 数字积木
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120562/D
// Memory Limit: 2048 MB
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

constexpr int MOD = 1e9 + 7;

template <class T>
constexpr T ksm(T a, ll b) {
    T res = 1;
    while (b) {
        if (b & 1)
            res *= a;
        b >>= 1;
        a *= a;
    }
    return res;
}

template <int P>
struct MInt {
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
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
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
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
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

template <>
int MInt<0>::Mod = 998244353;

template <int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

using Z = MInt<MOD>;

struct SafeZ {
    Z val = 1;
    int cnt = 0;

    SafeZ(Z v) {
        mul(v);
    }
    void mul(Z x) {
        if (x.val() == 0)
            cnt++;
        else
            val *= x;
    }
    void div(Z x) {
        if (x.val() == 0)
            cnt--;
        else
            val /= x;
    }
    Z get() {
        return cnt > 0 ? Z(0) : val;
    }
};

void init() {
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), pos(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i], pos[a[i]] = i;

    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
    }

    vector<bool> vis(n + 1);
    vector<int> pa(n + 1);
    int s = pos[0];
    vector<int> q;
    int h = 0;
    q.pb(s);
    vis[s] = 1;
    pa[s] = 0;
    while (h < q.size()) {
        int u = q[h++];
        for (auto v : g[u]) {
            if (vis[v])
                continue;
            vis[v] = 1;
            pa[v] = u;
            q.pb(v);
        }
    }

    vector<Z> way(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        int u = q[i];
        way[u] = 1;
        for (int v : g[u]) {
            if (v != pa[u]) {
                way[u] *= way[v] + 1;
            }
        }
    }

    vis.assign(n + 1, 0);
    vis[s] = 1;
    SafeZ cur = way[s];
    Z ans = cur.get();
    for (int k = 1; k < n; ++k) {
        int tar = pos[k];

        if (vis[tar]) {
            ans += cur.get();
            continue;
        }

        vector<int> path;
        int curr = tar;
        while (!vis[curr]) {
            path.pb(curr);
            curr = pa[curr];
        }
        reverse(all(path));

        cur.div(way[path[0]] + 1);
        for (int i = 0; i < path.size(); ++i) {
            int u = path[i];
            vis[u] = 1;
            cur.mul(way[u]);

            if (i < path.size() - 1) {
                cur.div(way[path[i + 1]] + 1);
            }
        }
        ans += cur.get();
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    cout << fixed << setprecision(15);
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}