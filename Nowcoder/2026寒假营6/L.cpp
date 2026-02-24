// Problem: 小L的游戏2
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120566/L
// Memory Limit: 512 MB
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

template <class Int>
struct Matrix {
    int n, m;
    vector<vector<Int>> a;

    Matrix(int n, Int val = Int())
        : n(n), m(n), a(n, vector<Int>(n, val)) {}
    Matrix(int n, int m, Int val = Int())
        : n(n), m(m), a(n, vector<Int>(m, val)) {}

    static Matrix identity(int n) {
        Matrix I(n, n);
        for (int i = 0; i < n; i++)
            I.a[i][i] = Int(1);
        return I;
    }

    vector<Int> &operator[](int i) {
        return a[i];
    }
    const vector<Int> &operator[](int i) const {
        return a[i];
    }

    Matrix operator+(const Matrix &other) const {
        assert(n == other.n && m == other.m);
        Matrix res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res[i][j] = a[i][j] + other[i][j];
        return res;
    }

    Matrix operator-(const Matrix &other) const {
        assert(n == other.n && m == other.m);
        Matrix res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res[i][j] = a[i][j] - other[i][j];
        return res;
    }

    Matrix operator*(const Matrix &other) const {
        assert(m == other.n);
        Matrix res(n, other.m, Int(0));
        for (int i = 0; i < n; i++)
            for (int k = 0; k < m; k++)
                for (int j = 0; j < other.m; j++)
                    res[i][j] = res[i][j] + a[i][k] * other[k][j];
        return res;
    }

    Matrix operator*(const Int &k) const {
        Matrix res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res[i][j] = a[i][j] * k;
        return res;
    }

    Matrix transpose() const {
        Matrix res(m, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res[j][i] = a[i][j];
        return res;
    }

    Matrix ksm(ll exp) const {
        assert(n == m);
        Matrix base = *this;
        Matrix res = identity(n);
        while (exp > 0) {
            if (exp & 1)
                res = res * base;
            base = base * base;
            exp >>= 1;
        }
        return res;
    }
};

template <class T>
T determinant(int n, Matrix<T> &mat) {
    T det(1, 0);
    int sign = 1;

    for (int i = 0; i < n; i++) {
        int pivot = i;
        while (pivot < n && mat[pivot][i].isZero())
            pivot++;
        if (pivot == n)
            return T();

        if (pivot != i) {
            swap(mat[i], mat[pivot]);
            sign = -sign;
        }

        det *= mat[i][i];
        for (int j = i + 1; j < n; j++) {
            if (!mat[j][i].isZero()) {
                T factor = mat[j][i] / mat[i][i];
                for (int k = i; k < n; k++) {
                    mat[j][k] -= factor * mat[i][k];
                }
            }
        }
    }

    if (sign == -1) {
        det = T() - det;
    }
    return det;
}

void init() {
}

void solve() {
    int m1, m2, n1, n2;
    ll z;
    cin >> m1 >> m2 >> n1 >> n2 >> z;
    Z p1, q1;
    cin >> p1 >> q1;
    Z p0 = 1 - p1, q0 = 1 - q1;
    int D = max({m1 + n1, m1 + n2, m2 + n1, m2 + n2});
    vector<Z> c(D + 1);
    c[m1 + n1] += p1 * q1;
    c[m1 + n2] += p1 * q0;
    c[m2 + n1] += p0 * q1;
    c[m2 + n2] += p0 * q0;
    vector<Z> L(D), R(D);
    ll st = z - D;
    for (ll x = z - 1; x >= st; --x) {
        int i = x - st;
        Z t1 = x + n1 < z ? L[x + n1 - st] : 0, t2 = x + n2 < z ? L[x + n2 - st] : 0;
        R[i] = q1 * t1 + q0 * t2;
        t1 = x + m1 < z ? R[x + m1 - st] : 1, t2 = x + m2 < z ? R[x + m2 - st] : 1;
        L[i] = p1 * t1 + p0 * t2;
    }
    if (st <= 0) {
        cout << L[-st] << endl;
        return;
    }
    Matrix<Z> T(D, Z(0));
    for (int j = 0; j < D; ++j)
        T[0][j] = c[j + 1];
    for (int i = 1; i < D; ++i)
        T[i][i - 1] = Z(1);

    T = T.ksm(st);
    Matrix<Z> base(D, 1, Z(0));
    for (int i = 0; i < D; ++i)
        base[i][0] = L[i];

    T = T * base;
    cout << T[0][0] << endl;
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