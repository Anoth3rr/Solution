// Problem: C. Rigged Bracket Sequence
// Contest: Codeforces - Codeforces Round 1082 (Div. 1)
// URL: https://codeforces.com/contest/2201/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

constexpr int MOD = 998244353;
constexpr int maxn = 3e5;

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

vector<Z> p2(maxn + 1);

void init() {
    p2[0] = 1;
    for (int i = 1; i <= maxn; ++i)
        p2[i] = p2[i - 1] * 2;
}

void solve() {
    int n;
    string s;
    cin >> n >> s;
    vector<int> B(n);
    int bal = 0;
    for (int i = 0; i < n; ++i) {
        bal += (s[i] == '(' ? 1 : -1);
        B[i] = bal;
    }

    Z Prod = Z(1), sb = Z(0);
    int len = 0;
    vector<Z> P(n);

    for (int p = 0; p < n; ++p) {
        if (s[p] == '(') {
            sb += p2[len];
        }
        len++;
        if (B[p] == 1) {
            Z val = p2[len] - sb;
            Prod *= val;
            sb = 0;
            len = 0;
        }
        P[p] = Prod * p2[len];
    }

    Z ans = 0;
    for (int r = 0; r < n; ++r) {
        if (s[r] == '(') {
            ans += p2[r];
        } else {
            if (r == 0)
                ans += Z(1);
            else
                ans += P[r - 1];
        }
    }
    cout << ans << endl;
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