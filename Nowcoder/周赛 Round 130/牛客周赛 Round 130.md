# A 红美铃的访客登记

用一个标记记录有没有扫到非 $0$ 数字即可。

```cpp
void solve() {
    string s;
    bool f = 1;
    cin >> s;
    for (auto v : s) {
        if (f && v == '0')
            continue;
        else
            f = 0, cout << v;
    }
    cout << endl;
}
```

但是输入存成整型本来就会忽略前导零，所以直接读入然后输出就行。

```cpp
void solve() {
    int x;
    cin >> x;
    cout << x << endl;
}
```

# B 爱丽丝的魔力零件分类

检查 $\text{T}$ 和 $\text{L}$ 每个点的度数发现 ， $\text{T}$ 为 $\{1,3,1,1\}$ ，$\text{L}$ 为 $\{1,1,2,2\}$ ，所以我们只需要检查是否有一个点周围的 $*$ 的个数为 $3$ 即可。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (int i = 0; i < n; ++i)
        cin >> g[i];

    bool f = false;
    auto check = [&](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < n;
    };

    for (int i = 0; i < n && !f; ++i) {
        for (int j = 0; j < n && !f; ++j) {
            if (g[i][j] == '*') {
                int cnt = 0;
                for (int k = 0; k < 4; ++k) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (check(nx, ny) && g[nx][ny] == '*')
                        ++cnt;
                }
                if (cnt == 3)
                    f = true;
            }
        }
    }
    cout << (f ? "T" : "L") << endl;
}
```

# C 博丽大结界的稳定轴心

如果一个点不是根节点，它的孩子数就是度数 $-1$ 。所以如果有度大于 $3$ 的点，就一定不能构成二叉树 $0$ ；度等于 $3$ 的点一定不能作为根节点；剩下的都可以作为根节点。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> deg(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        deg[u]++, deg[v]++;
    }
    int cnt = 0;
    for (auto v : deg) {
        if (v > 3) {
            cout << 0 << endl;
            return;
        } else if (v == 3) {
            cnt++;
        }
    }
    cout << n - cnt << endl;
}
```

# D 魔法人偶的十进制校准

很容易能想到 $1\sim 8$ 可以使用 $\frac{b}{9} = 0.bbbbb...$ 来构造。

$0$ 和 $9$ 我们可以根据 $a$ 的奇偶性进行分类，有：

- $\frac{1}{11} = 0.0909...,\frac{10}{11} = 0.9090...$

```cpp
void solve() {
    int a, b;
    cin >> a >> b;
    if (b == 0) {
        if (a & 1)
            cout << 1 << " " << 11 << endl;
        else
            cout << 10 << " " << 11 << endl;
    } else if (b == 9) {
        if (a & 1)
            cout << 10 << " " << 11 << endl;
        else
            cout << 1 << " " << 11 << endl;
    } else {
        int g = gcd(b, 9);
        cout << b / g << " " << 9 / g << endl;
    }
}
```

# E 爱丽丝的人偶圆舞曲

我们不妨枚举步长 $d$ ，用 $dp[i][j]$ 记录第 $i$ 位为 $j$ 结尾的字符串可以保留几个原来字符串的字符，记 $j$ 的前一个匹配的字符为 $prev = (j-d+26)\%26$ ，后一个匹配的字符为 $next = (j+d)\%26$ ，不难得到状态转移方程为
$$
dp[i][j] = max(dp[i-1][prev],dp[i-1][next])+(s[i]-'a')==j
$$
这里用滚动 $dp$ 实现。

```cpp
void solve() {
    string s;
    cin >> s;
    int n = s.size(), mx = 0;
    for (int d = 0; d <= 13; ++d) {
        array<int, 26> dp{}, ndp{};
        for (int i = 0; i < 26; ++i)
            dp[i] = (s[0] - 'a') == i;
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < 26; ++j) {
                ndp[j] = max(dp[(j - d + 26) % 26], dp[(j + d) % 26]) + (j == s[i] - 'a');
            }
            dp.swap(ndp);
        }
        for (auto v : dp)
            mx = max(mx, v);
    }
    cout << n - mx << endl;
}
```

# F 红魔馆的微瑕序位

不难发现，如果混乱度为 $2$ ，必然是相差为 $1$​ 的两个元素交换位置。所以我们的目标状态 $T$ 即为 $[1,2,...,n]$ 交换了一组 $(k,k+1)$ 。

给定一个排列，将其还原为目标状态所需的最少交换次数等于 $n−c$ ，其中 $n$ 是元素个数，$c$ 是将当前排列与目标排列连边后形成的置换环的数量。

引入 $(k,k+1)$ 的交换后，如果这两个元素在同一个置换环中，交换它们就会断开这个环，操作次数变为 $n-c+1$ ，如果这两个元素不在同一个置换环中，交换它们会合并这两个环，操作次数变为 $n-c-1$ 。

置换环：将当前排列中的每个元素视为一个节点，如果元素 $a[i]$ 应该位于位置 $i$，则从 $i$ 指向 $a[i]$，最终整个排列会形成一个或多个不相交的环状结构。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    vector<int> id(n + 1);
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (!id[i]) {
            cnt++;
            int cur = i;
            while (!id[cur]) {
                id[cur] = cnt;
                cur = a[cur];
            }
        }
    }
    int f = -1;
    for (int i = 1; i < n; ++i) {
        if (id[i] == id[i + 1]) {
            f = 1;
            break;
        }
    }
    cout << n - cnt - f << endl;
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

