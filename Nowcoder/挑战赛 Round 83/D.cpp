//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(),a.rend()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef __int128 lll;
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

template<class T>
constexpr T ksm(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(long long v) : x{norm(v % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if (P > 0) return P;
        else return Mod;
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr static int norm(long long v) {
        if (v < 0) v += getMod();
        if (v >= getMod()) v -= getMod();
        return int(v);
    }

    constexpr int val() const { return x; }
    explicit constexpr operator int() const { return x; }

    constexpr MInt operator-() const {
        return MInt(norm(getMod() - x));
    }

    constexpr MInt inv() const {
        assert(x != 0);
        return pow(getMod() - 2);
    }

    constexpr MInt pow(long long e) const {
        MInt res(1), base(*this);
        while (e > 0) {
            if (e & 1) res *= base;
            base *= base;
            e >>= 1;
        }
        return res;
    }

    constexpr MInt &operator*=(MInt rhs) & {
        x = int(1LL * x * rhs.x % getMod());
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

    friend constexpr MInt operator*(MInt lhs, MInt rhs) { return lhs *= rhs; }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) { return lhs += rhs; }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) { return lhs -= rhs; }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) { return lhs /= rhs; }

    friend istream &operator>>(std::istream &is, MInt &a) {
        long long v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }

    friend constexpr bool operator==(MInt lhs, MInt rhs) { return lhs.val() == rhs.val(); }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) { return lhs.val() != rhs.val(); }
};

template<>
int MInt<0>::Mod = 998244353;

typedef MInt<MOD> Z;

void init() {

}

void solve() {
    ll n, m;
    cin >> n >> m;

    ll l = min(n, m);

    vector<array<ll, 3>> seg;
    for (ll j = 1; j <= l; ) {
        ll w = m / j, r = (w ? min(l, m / w) : l);
        seg.pb({j, r, w});
        j = r + 1;
    }

    vector<Z> pre(seg.size() + 1);
    pre[0] = Z(1);
    for (int k = 0; k < seg.size(); ++k) {
        pre[k + 1] = pre[k] * ksm(Z(seg[k][2]), seg[k][1] - seg[k][0] + 1);
    }

    Z ans = 0;

    Z P = 1;
    ll nj = 0, i = 1;
    while (i <= l) {
        Z v = n / i;
        ll r = n / (n / i);
        if (r > l) r = l;

        ll t = i;
        while (t <= r) {
            while (nj < seg.size() && seg[nj][1] < t) ++nj;
            if (nj >= seg.size()) break;
            Z w = seg[nj][2];
            ll st = max(t, seg[nj][0]);
            ll ed = min(r, seg[nj][1]);
            ll len = ed - st + 1;

            Z C = pre[nj] * w * ksm(v, seg[nj][0]);

            if (v * w != 1) {
                ans += C * ksm(v * w, st - seg[nj][0]) * (ksm(v * w, len) - 1) / (v * w - 1);
            } else {
                ans += C * ksm(v * w, st - seg[nj][0]) * Z(len);
            }

            t = ed + 1;
        }

        i = r + 1;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}