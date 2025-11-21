# A 小苯的数字染色

简单来说，任何一个大于 $1$ 的数字都可以表示为 $a$ 个 $2$ 和 $b$ 个 $3$ 的和（$0\leq a,b$）

简单证明：

$\begin{align*}2x+3y&=n \\2(x+y)+y&=n\end{align*}$

令 $a = (x+y),b = y$ ，$0\leq b\leq a$，得 $2a+b=n$

可以把他看成， $n\div a=2 \cdots b$，显然任何一个整数除以 2 都有商和余数。

需要注意，$n=1$ 时不满足 $0\leq b\leq a$。

```cpp
void solve() {
    int n;
    cin >> n;
    if (n == 1) cout << "NO" << "\n";
    else cout << "YES" << "\n";
}
```

# B 小苯的数组重排

化简一下式子，$S = a_1 + 2a_2 + ... + 2a_{n-1} + a_n$，很显然减掉最小的两个数字即可。

```cpp
void solve() {
    int n, mn1 = inf, mn2 = inf;
    ll sum = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        sum += x;
        if (x < mn1) mn2 = mn1, mn1 = x;
        else if (mn1 <= x && x < mn2) mn2 = x;
    }
    cout << 2 * sum - mn1 - mn2 << "\n";
}
```

# C 小苯的麦克斯

首先可以看出：

- 区间越小越好，因为干扰的数字少
- 对于一个长度为 $2$ 的区间，记较大数字为 $x$ ，较小数字为 $y$ ，$MAX-MEX=x-[y==0]*(1+[x==1])$ 。

检查每一个长度为 $2$ 的区间即可。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    ll ans = -INF;
    for (int i = 1; i < n; ++i) {
        ll x = max(a[i], a[i - 1]), y = min(a[i], a[i - 1]);
        ans = max(ans, x - (y == 0) * (1 + (x == 1)));
    }
    cout << ans << "\n";
}
```

# D 小苯的平衡序列

排序一下，删最大或者最小，看看哪个平衡度小即可。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(all(a));
    ll m1 = a[n / 2 - 1], m2 = a[n / 2];
    ll s1 = abs(a[0] - m1), s2 = abs(a[n - 1] - m2);
    for (int i = 1; i < n - 1; ++i) {
        s1 += abs(a[i] - m1);
        s2 += abs(a[i] - m2);
    }
    cout << min(s1, s2) << "\n";
}
```

# E 小苯的数字变换

一个子串的数字和对 $9$ 取模等于该子串各位数字之和对 $9$ 取模。

打表发现 $f(x) =\begin{cases}0&x=0\\x\%9&x\%9>0\\9&x\%9==0\end{cases}$

记 $P_i$ 为长度为 $i$ 的前缀数位和， $S_{i,j}\ mod\ 9 \equiv (P_{j}-P_{i-1})\ mod\ 9$ 。所以统计 模为 $r$ 的子串个数 ，对于固定 $j$（右端），所有满足 $(P_{j}-P_{i-1})\ mod\ 9 = r$ 的 $i$ 等价于 $$P_{i-1}\equiv (P_j-r)\ \ (mod\ 9)$$

扫一遍统计一下即可。

注意在统计的时候，我们把 $0$ 当成 $9$ 处理了，所以还要减去 $0$ 串。

```cpp
void solve() {
    string s;
    cin >> s;
    int n = s.size();
 
    vector<int> cnt(9);
 
    ll ans = 0;
    int prev = 0;
    cnt[0] = 1;
 
    for (int i = 0; i < n; i++) {
        int d = s[i] - '0';
        prev = (prev + d) % 9;
 
        for (int m = 0; m < 9; m++) {
            int v = (prev - m + 9) % 9;
            ans += cnt[m] * (v ? v : 9);
        }
        cnt[prev]++;
    }
 
    ll counts = 0;
    ll len = 0;
    for (char c : s) {
        if (c == '0') {
            len++;
            counts += len;
        } else {
            len = 0;
        }
    }
    ans -= 9 * counts;
 
    cout << ans << "\n";
}
```

# F 小苯的序列合并

从高位往低位尝试放 $1$ ，判断是否存在一种分割，使得能够在不影响已经放完的位的情况下，把当前位置 $1$ 。用前缀异或和判断 $sum\ \&\ cand\ ==\ cand$ 即可。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    ll ans = 0;
    for (int i = 30; i >= 0; --i) {
        int cand = ans | (1 << i), prev = 0;
        bool ok = false;
        unordered_set<int> vis;
        vis.insert(0);
        for (int i = 0; i < n; ++i) {
            prev ^= a[i];
            int t = prev & cand;
            if (vis.find(cand ^ t) != vis.end()) {
                if (i == n - 1) ok = true;
                vis.insert(t);
            }
        }
        if (ok) ans = cand;
    }
    cout << ans << "\n";
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
    cin.tie(0); cout.tie(0);

    init();

    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    return 0;
}
```