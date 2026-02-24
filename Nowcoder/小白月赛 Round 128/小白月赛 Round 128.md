# A 模糊匹配

手写一下模糊比较函数即可。

```cpp
void solve() {
    int n;
    string s1, s2;
    cin >> n >> s1 >> s2;
    auto cmp = [&](char a, char b) -> bool {
        vector<string> f = {"0O", "1Il"};
        for (auto s : f) {
            for (auto c1 : s)
                for (auto c2 : s)
                    if (a == c1 && b == c2)
                        return true;
        }
        return a == b;
    };
    for (int i = 0; i < n; ++i) {
        if (!cmp(s1[i], s2[i])) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
}
```

# B 只留专一数

不难发现，一个数的幂和它本身专一性相同。所以本题等价于找这个数组中是否有专一数（素数的幂或 $1$ ）。

```cpp
void solve() {
    int n;
    cin >> n;
    bool f = 0;
    auto check = [&](int n) {
        int p = -1;

        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                p = i;
                while (n % i == 0)
                    n /= i;
                break;
            }
        }

        if (p == -1)
            return true;

        return n == 1;
    };
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        if (!f && check(x))
            f = 1;
    }
    cout << (f ? "YES" : "NO") << endl;
}
```

# C 左右左右左左右，左右左左右

贪心模拟一下放置即可。

```cpp
void solve() {
    int n;
    ll x, y;
    cin >> n >> x >> y;
    if (x == y && x == 0) {
        cout << string(n, '0') << endl;
        return;
    }
    string ans;
    ll S = 0;
    for (int i = 1; i <= n; ++i) {
        if (llabs(S - y) <= S + x) {
            ans += '0';
            S -= y;
        } else {
            ans += '1';
            S += x;
        }
    }
    cout << ans << endl;
}
```

# D 进退的艺术

考虑一个 $a_i$ ，有 $t$ 个 $a_j$ 满足 $a_i+a_j\leq m$ （即 $a_j\leq m-a_i$ ），$n-t-1$ 个 $a_j$ 满足 $a_i+a_j>m$ （即 $a_j>m+a_i$ ），最后的心情为
$$
ta_i - \sum\limits_{a_i+a_j>m}a_j
$$
我们排序一下二分求 $t$ ，用前缀和求和即可。

```cpp
void solve() {
    int n;
    ll m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i], b[i] = a[i];
    sort(all(b));
    vector<ll> pre(n + 1);
    for (int i = 0; i < n; i++)
        pre[i + 1] = pre[i] + b[i];
    for (int i = 0; i < n; i++) {
        ll p = upper_bound(all(b), m - a[i]) - b.begin();
        ll ans = p * a[i] - pre[n] + pre[p];
        if (2 * a[i] <= m) {
            ans -= a[i];
        } else {
            ans += a[i];
        }

        cout << ans << " ";
    }
    cout << endl;
}
```

# E 扫雷难度调节

如果我们能找到一个覆盖所有格子的最小地雷集合（最小支配集），设其大小为 $M_{min}$，那么我们能得到的最大数字格数量为 $K_{max}=N\times M−M_{min}$ 。如果题目要求的 $k\leq K_{max}$，我们就可以在最小支配集的基础上，额外将 $K_{max}−k$ 个数字格变成地雷，从而正好使得数字格数量为 $k$ 。

对于规则图形（矩形）的支配集问题，最优解通常呈现规则的晶格状分布。虽然在极小的边界条件下可能存在非规则的最优解，但在 $N,M$ 较大的情况下，内部区域一定符合 $3\times 3$ 分布。边界的微扰通过枚举所有可能的偏移量可以被涵盖。我们可以尝试所有的 $3\times 3$ 的基础模式放完固定地雷，然后在没有被覆盖的地方原地补一个雷。

比较这 $9$ 种尝试的结果，取地雷总数最小的结果即可。

（当然你可以根据以上的分析，分类讨论 $3k\times 3k,(3k+1)\times 3k$ 等情况）
```cpp
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
 
    int tot = n * m;
    int mn = tot + 1;
    int R = 0, C = 0;
 
    vector<bool> vis;
 
    auto mark = [&](int x, int y) {
        int sr = max(x - 1, 0);
        int sc = max(y - 1, 0);
        x = min(x + 1, n - 1);
        y = min(y + 1, m - 1);
 
        for (int r = sr; r <= x; ++r) {
            for (int c = sc; c <= y; ++c) {
                vis[r * m + c] = 1;
            }
        }
    };
 
    for (int pr = 0; pr < 3; ++pr) {
        for (int pc = 0; pc < 3; ++pc) {
            vis.assign(tot, 0);
 
            int cnt = 0;
            for (int i = pr; i < n; i += 3) {
                for (int j = pc; j < m; j += 3) {
                    cnt++;
                    mark(i, j);
                }
            }
 
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (!vis[i * m + j]) {
                        cnt++;
                        mark(i, j);
                    }
                }
            }
 
            if (cnt < mn) {
                mn = cnt;
                R = pr;
                C = pc;
            }
        }
    }
 
    if (tot - mn < k) {
        cout << "-1" << endl;
    } else {
        vector<int> g(tot);
        vis.assign(tot, 0);
        int cur = 0;
 
        for (int i = R; i < n; i += 3) {
            for (int j = C; j < m; j += 3) {
                g[i * m + j] = 1;
                cur++;
                mark(i, j);
            }
        }
 
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (!vis[i * m + j]) {
                    g[i * m + j] = 1;
                    cur++;
                    mark(i, j);
                }
            }
        }
 
        int res = (tot - cur) - k;
 
        for (int i = 0; i < tot && res > 0; ++i) {
            if (g[i] == 0) {
                g[i] = 1;
                res--;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << g[i * m + j];
            }
            cout << endl;
        }
    }
}
```

# F 徽章计数

对于每个数值 $x$ ，如果有 $cnt[x]$ 个小朋友，那么这些小朋友必须被分成 $\frac{cnt[x]}{x}$ 组（无法整除则方案数为 $0$ ）

那么分组的方案数为（要分成 $g=\frac{cnt[x]}{x}$ 组）
$$
\frac{cnt[x]!}{(x!)^g\cdot g!}
$$
其中除以 $g!$ 是因为这 $g$ 个组在未分配具体徽章前是不可区分的。

然后我们从 $m$ 个勋章里面选出 $\sum g_x$ 个分给这些组即可。

注意 $m$ 的范围是 $10^9$ ，需要手写排列数公式。 

```cpp
void solve() {
    int n, m;
    cin >> n >> m;
    unordered_map<int, int> cnt;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        cnt[x]++;
    }
    int s = 0;
    Z ans = 1;
    for (auto [u, v] : cnt) {
        if (v % u != 0) {
            cout << 0 << endl;
            return;
        }
        int g = v / u;
        s += g;
        ans *= C.fac(v) / ksm(C.fac(u), g) / C.fac(g);
    }
    auto A = [&](int n, int m) -> Z{
        Z res = 1;
        for (int i = n; i >= n - m + 1; --i) {
            res *= i;
        }
        return res;
    };
    cout << A(m, s) * ans << endl;
}
```

# 头文件

```cpp
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

void init() {
}

void solve() {
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
```

# 自动取模

```cpp
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
```

# 组合数学

```cpp
struct Comb {
    int n;
    vector<Z> _fac, _inv;

    Comb() : n(0), _fac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
    void init(int m) {
        if (m <= n)
            return;
        _fac.resize(m + 1);
        _inv.resize(m + 1);
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _inv[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _inv[i - 1] = _inv[i] * i;
        }
        n = m;
    }
    Z fac(int x) {
        if (x > n)
            init(x);
        return _fac[x];
    }
    Z inv(int x) {
        if (x > n)
            init(x);
        return _inv[x];
    }
    Z C(int x, int y) {
        if (x < 0 || y < 0 || x < y)
            return 0;
        return fac(x) * inv(y) * inv(x - y);
    }
    Z A(int x, int y) {
        if (x < 0 || y < 0 || x < y)
            return 0;
        return fac(x) * inv(x - y);
    }
};
```