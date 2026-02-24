# A 幂运算

构造 $a^1=n$ 即可。

```cpp
void solve() {
    int x;
    cin >> x;
    cout << x << " " << 1 << "\n";
}
```

# B 琪露诺的 K 维偏序

二分查找数组中小于 $x$ 的元素个数即可。

```cpp
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    while (q--) {
        int k, x;
        cin >> k >> x;
        int pos = lower_bound(all(a), x) - a.begin();
        if (pos >= k) cout << "Yes" << "\n";
        else cout << "No" << "\n";
    }
}
```

# C 合成大企鹅

不难发现，最后的结果为：
$$
\sqrt{a_1\times \sqrt{a_2\cdots \sqrt{a_{n-1}\times a_{n}}}}
$$
所以让大数尽可能少的被开根号即可。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(all(a));
    double ans = a[0];
    for (int i = 1; i < n; ++i) {
        ans *= a[i];
        ans = sqrt(ans);
    }
    cout << ans << "\n";
}
```

# D/E ⑨运算

因为每一位都是 $\text{9}$ ，所以最终一定为 $N=10^k-1$ ，且必然$\mod 9 = 0$。因为 $+9$ 不改变取模结果， $\times 9$ 会改变取模结果。

所以如果原来数字是 $\text{9}$ 的倍数，那么只需要执行 $+9$ ，答案为 $(N-x)/9$ 。

如果不是 $9$ 的倍数就在其中插入一次 $\times 9$ ，即先做 $a$ 次 $+9$ ，再做一次 $\times 9$ ，再做 $b$ 次 $+9$ ，即：
$$
x \rightarrow x+9a\rightarrow 9x+81a\rightarrow9x+9(9a+b)
$$
所以 $9a+b=(N-9x)/9$ ，最小化 $a+b$ 即可。

```cpp
vector<ll> p(19);

void init() {
    p[0] = 1;
    for (int i = 1; i <= 18; ++i) p[i] = p[i - 1] * 10;
}

void solve() {
    ll x;
    cin >> x;
    ll ans = INF;
    for (int i = 1; i <= 18; ++i) {
        ll N = p[i] - 1;
        if ((x % 9) == 0 && N >= x ) {
            ll q = (N - x) / 9;
            if (q < ans) ans = q;
        }
        if (N >= 9 * x) {
            ll S = (N - 9 * x) / 9;
            ll q = 1 + S / 9 + S % 9;
            if (q < ans) ans = q;
        }
    }
    cout << ans << "\n";
}
```

# F 琪露诺的连续取模求和

对每个整数 $i$ 依次做模 $q,q-1,\dots,p$ ：

- 若 $i<p$ ，没有任何模会改变它，结果就是 $i$ 。
- 若 $p\le i\le q$ ，当遍历到模数 $m=i$ 时有 $i\%i=0$ ，所以结果为 $0$ 。
- 若 $i>q$ ，先做一次 $r=i\%q$ （于是 $0\le r<q$ ）。接下来会继续使用 $q-1,q-2,\dots,p$ ，然后操作同上。

因此有：
$$
f(i)=\begin{cases} i,& i<p,\\ i\%q,& i\ge p\ \text{and}\ i\%q<p,\\ 0,& \text{others}. \end{cases}
$$
于是对区间 $[l,r]$ 求和可以分两部分：

1. $i<p$ 的那段直接用等差和；
2. $i\ge p$ 的那段只在 $i\%q<p$ 时贡献 $i\%q$ ，对这段按模 $q$ 的完整周期与残余计算即可（每个周期对小于 $p$ 的余数贡献为 $\sum\limits_{x=0}^{p-1}x=\tfrac{p(p-1)}2$ 。

```cpp
void solve() {
    int l, r, p, q;
    cin >> l >> r >> p >> q;

    auto sum = [&](int a, int b) -> ll{
        if (a > b) return 0ll;
        return 1ll * (a + b) * (b - a + 1) / 2;
    };

    auto calc = [&](int x, int p, int q) -> ll {
        if (x < 0) return 0l;
        ll n = x + 1, m = min(n % q, (ll)p);
        return 1ll * n / q * p * (p - 1) / 2 + m * (m - 1) / 2;
    };

    ll ans = 0;
    int a = l;
    int b = min(r, p - 1);
    if (a <= b) ans += sum(a, b);

    int L = max(l, p);
    if (L <= r) ans += calc(r, p, q) - calc(L - 1, p, q);
    cout << ans << "\n";
}
```

# G 琪露诺的排列构造

如果 $n=1$ 或 $n=2$ 显然不可能。

如果 $n$ 为奇数且 $n>3$ ，整个排列向左移动一位即可，前 $n-1$ 项为 $2i+1$ ，最后一项为 $n+1$ 。

如果 $n$ 为偶数：

- 如果 $n$ 是 $\text{4}$ 的倍数，用 $[a+1,a+3,a,a+2]$ 即可。
- 否则，先构造一个 $6$ 块 $[2,3,1,6,4,5]$ ，再拼接 $4$ 块即可。

构造短块手玩一下即可。

```cpp
void solve() {
    int n;
    cin >> n;
    if (n == 1 || n == 2) {
        cout << -1 << "\n";
        return;
    }
    vector<int> p(n + 1, 0);
    if (n % 2 == 1) {
        for (int i = 1; i < n; ++i) p[i] = i + 1;
        p[n] = 1;
    } else {
        if (n % 4 == 0) {
            for (int a = 1; a <= n; a += 4) {
                p[a] = a + 1;
                p[a + 1] = a + 3;
                p[a + 2] = a;
                p[a + 3] = a + 2;
            }
        } else {
            p[1] = 2;
            p[2] = 3;
            p[3] = 1;
            p[4] = 6;
            p[5] = 4;
            p[6] = 5;
            for (int a = 7; a <= n; a += 4) {
                p[a] = a + 1;
                p[a + 1] = a + 3;
                p[a + 2] = a;
                p[a + 3] = a + 2;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << p[i] << " ";
    }
    cout << "\n";
}
```

# 头文件

```cpp
//Another
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
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}
```

