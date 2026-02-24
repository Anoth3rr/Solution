// Problem: 种树
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/119900/F
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

constexpr int MOD = 1e9 + 7;
using Z = MInt<MOD>;

constexpr int maxn = 1e6;

Z Sn(Z n) {
    return n * (n + 1) / 2;
}
Z Sn2(Z n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

unordered_map<int, Z> fMu;

vector<int> spf(maxn + 1), primes, phi(maxn + 1), mu(maxn + 1);
vector<Z> smu(maxn + 1);

Z sumMu(int n) {
    if (n <= maxn) {
        return smu[n];
    }
    if (fMu.count(n)) {
        return fMu[n];
    }
    if (n == 0) {
        return 0;
    }
    Z ans = 1;
    int l = 2, r;
    while (l <= n) {
        r = n / (n / l);
        ans -= (Sn2(Z(r)) - Sn2(Z(l - 1))) * sumMu(n / l);
        l = r + 1;
    }
    return fMu[n] = ans;
}

void init() {
    mu[1] = 1, smu[1] = 1;

    for (int i = 2; i <= maxn; i++) {
        if (!spf[i])
            spf[i] = i, mu[i] = -1, primes.push_back(i);

        for (int j = 0; primes[j] * i <= maxn; j++) {
            int m = primes[j] * i;
            spf[m] = primes[j];

            if (i % primes[j] == 0) {
                mu[m] = 0;
                break;
            }
            mu[m] = -mu[i];
        }

        if (mu[i] == 1)
            smu[i] = smu[i - 1] + Z(i) * i;
        else if (mu[i] == -1)
            smu[i] = smu[i - 1] - Z(i) * i;
        else
            smu[i] = smu[i - 1];
    }
}

void solve() {
    int n;
    cin >> n;

    Z ans = 0;

    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans += (sumMu(r) - sumMu(l - 1)) * Sn(Z(n / l)) * Sn(Z(n / l));
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