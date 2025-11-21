# A 小彩找数

记录一下输出即可。

```cpp
void solve() {
    vector<int> a(4);
    for (int i = 1; i <= 3; ++i) {
        int x;
        cin >> x;
        a[x] = i;
    }
    for (int i = 1; i <= 3; ++i) cout << a[i] << " ";
    cout << "\n";
}
```

# B 小彩的好字符串

$n$ 就 $2000$ ，暴力即可。

```cpp
void solve() {
    int n;
    string s;
    cin >> n >> s;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        vector<int> a(4);
        for (int j = i; j < n; ++j) {
            a[s[j] - '0']++;
            if (a[1] == a[2] && a[2] == a[3]) cnt++;
        }
    }
    cout << cnt << "\n";
}
```

# C 小彩的字符串交换

用长度为 $3$ 的窗口判一遍即可。

```cpp
void solve() {
    int n, ans = 3;
    string s;
    cin >> n >> s;
    vector<int> a(4);
    for (auto v : s) a[v - '0']++;
    if (!(a[1] && a[2] && a[3])) {
        cout << -1 << "\n";
        return;
    }
    a.assign(4, 0);
    a[s[0] - '0']++, a[s[1] - '0']++;
    for (int i = 2; i < n; ++i) {
        a[s[i] - '0']++;
        if (a[1] && a[2] && a[3]) {
            cout << 0 << "\n";
            return;
        } else {
            ans = min(ans, 3 - (a[1] > 0) - (a[2] > 0) - (a[3] > 0));
        }
        a[s[i - 2] - '0']--;
    }
    cout << ans << "\n";
}
```

# D 小彩的数组选数

显然是打家劫舍，如果第 $i$ 位被选择了那么第 $i-1$ 和 $i+1$ 位就不能选，综合一下就是要选第 $i$ 位就不能选第 $i-1$ 位。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    if (n == 1) cout << a[1] << "\n";
    else {
        dp[1] = a[1];
        for (int i = 2; i <= n; ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + a[i]);
        }
        cout << dp[n] << "\n";
    }
}
```

# E 小彩的数组构造

**为了表述方便，以下描述中，子数组均指长度为 $3$ 的子数组。**

由 “和为 $1$ 的倍数的子数组有 $a$ 个” ，得数组的长度为 $a+2$ 。

由 “和为 $2$ 的倍数的子数组有 $b$ 个” 和 "和为 $3$ 的倍数的子数组有 $c$ 个" ，得 “和为 $6$ 的倍数的子数组有 $min(b,c)$ 个” 。

也就是说，对于每一个子数组，它都落到以下四种情况中：

- 同时被 $2$ 和 $3$ 整除， $x=min(b,c)$ 个。
- 仅被 $2$ 整除， $b-x$​ 个。
- 仅被 $3$ 整除， $c-x$​ 个。
- 都不整除， $a-x-(b-x)-(c-x)$ 个。

有解的情况为 $max(0,b+c-a) \leq x\leq min(b,c)$

用 $s[i]$ 表示第 $i$ 个子数组的和模 $6$ 的余数，我们就要解以下同余方程组：
$$
m_i+m_{i+1}+m_{i+2}\equiv s[i](mod\ 6),i = 1\sim a
$$
我们不妨取 $m[1]=m[2]=0$ 进行递推，得到所有的 $m$ ，最后取同余的正整数值即可。 

```cpp
void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    int n = a + 2;
    int x = max(b + c - a, 0);
    if (b > a || c > a || x > min(b, c)) {
        cout << -1 << "\n";
        return;
    }
    int y = a - x - (b - x) - (c - x);
    if (a == 0) {
        cout << "1 1" << "\n";
        return;
    }
    vector<int> s;
    for (int i = 0; i < x; ++i) s.pb(0);
    for (int i = 0; i < b - x; ++i) s.pb(2);
    for (int i = 0; i < c - x; ++i) s.pb(3);
    for (int i = 0; i < y; ++i) s.pb(1);
    vector<int> m(n + 1);
    m[1] = m[2] = 0;
    for (int i = 1; i <= a; ++i) {
        int val = ((s[i - 1] - m[i] - m[i + 1]) % 6 + 6) % 6;
        m[i + 2] = val;
    }
    for (int i = 1; i <= n; ++i) {
        cout << m[i] + 6 << " ";
    }
    cout << "\n";
}
```

# F 小彩的好数构造

$$
\begin{array}{rr}
   & 1212 \\
\times & 1001 \\
\hline
   & 1212 \\
 + & 1212000 \\
\hline
   & 1213212 \\
\end{array}
$$


不难想到去构造 $b=100...001$ 的情况下对应的 $a$ 。

如果 $n$ 为偶数，显然 $12...12\times 10...01$ 为 $12...1232...1212$ 。

如果 $n$ 为大于 $3$ 的奇数，只需要在 $12...12$ 的中间任意位置插入一个 $3$ 即可，在列竖式的形式下， $3$ 会落在一个空列上：
$$
\begin{array}{rr}
& 12312 \\
\times & 10001 \\
\hline
& 12312 \\
+ & 123120000 \\
\hline
& 123132312 \\
\end{array}
$$
然后特殊构造 $n=3$ 的时候的解即可。

```cpp
void solve() {
    int n;
    cin >> n;
    if (n == 1) cout << -1 << "\n";
    else if (n == 3) cout << "131" << " " << "101" << "\n";
    else if (n & 1) {
        for (int i = 0; i < n / 2 - 1; ++i) cout << 12;
        cout << 312 << " " << 1;
        for (int i = 0; i < n - 2; ++i) cout << 0;
        cout << 1 << "\n";
    } else {
        for (int i = 0; i < n / 2; ++i) cout << 12;
        cout << " " << 1;
        for (int i = 0; i < n - 2; ++i) cout << 0;
        cout << 1 << "\n";
    }
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