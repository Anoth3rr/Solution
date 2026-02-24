# A 小红的双层夹心

判断第 $2$ 个字符和第 $3$ 个字符是否相等即可。

```cpp
void solve() {
    string s;
    cin >> s;
    cout << (s[1] == s[2] ? "Yes" : "No") << endl;
}
```

# B 小红的马卡龙定位

读入三个坐标，排序一下，中间的就是答案。

需要注意你的做法有没有考虑横坐标或纵坐标全相等的情况。

```cpp
void solve() {
    vector<array<int, 3>> a(3);
    for (int i = 0; i < 3; ++i)
        cin >> a[i][0] >> a[i][1], a[i][2] = i;
    sort(all(a));
    cout << a[1][2] + 1 << endl;
}
```

# C 小红的奶油蛋糕工坊

我们设 $k=\left\lceil\frac{n}{2}\right\rceil$ ，我们只需要让 $1\sim k$ 全部变成 $\left\lceil\frac{k}{2}\right\rceil$ 即可。

```cpp
void solve() {
    int n;
    cin >> n;
    int k = (n + 1) / 2;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        if (1 <= x && x <= k)
            cout << (1 + k) / 2 << " ";
        else
            cout << x << " ";
    }
    cout << endl;
}
```

# D 小红的奇数奶油球

计算每个节点对应的子树大小，删去节点 $v$ 后会被分成几个部分：孩子子树 $siz[son(v)]$ ，父亲子树 $n-1-\sum siz[son(v)]$ 。检查每个节点即可。（注意父亲子树的大小可以为 $0$ ）

```cpp
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    if (n == 1) {
        cout << 1 << endl;
        return;
    }
    vector<int> siz(n + 1), fa(n + 1);
    function<void(int, int)> dfs = [&](int u, int p) {
        siz[u] = 1;
        fa[u] = p;
        for (auto v : g[u]) {
            if (v == p)
                continue;
            dfs(v, u);
            siz[u] += siz[v];
        }
    };
    dfs(1, 0);
    int ans = 0;
    for (int u = 1; u <= n; ++u) {
        int o = n - 1;
        bool f = true;
        for (auto v : g[u]) {
            if (v == fa[u])
                continue;
            if (!(siz[v] & 1)) {
                f = false;
                break;
            }
            o -= siz[v];
        }
        if (f && ((o & 1) || o == 0))
            ans++;
    }
    cout << ans << endl;
}
```

# E 小红的提拉米苏配方（easy）

因为处理到无法处理时截止，所以设 $1$ 的数量为 $cnt$ ，一定删除了 $p=\lfloor\frac{cnt}{2}\rfloor$ 个 $1$ 并修改了相同数量的 $2$ 。

为了使字典序最小，我们把最右边的 $p$ 个 $1$ 改成 $2$ ，剩下的 $1$ 删除即可。

如果有奇数个 $1$ ，我们就遍历每个 $1$ ，如果它的右边第一个字符是 $2$ 我们就保留，$0$ 就删除，多个右边是 $2$ 的 $1$ 保留第一个，如果右侧相邻全是 $0$ 就保留最后一个。

```cpp
void solve() {
    string s;
    cin >> s;
    int n = s.size(), pos = -1;
    vector<int> idx;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            idx.pb(i);
        }
    }
    char p = '.';
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] != '1')
            p = s[i];
        else if (p == '2')
            pos = i;
    }
    if (!idx.size()) {
        cout << s << endl;
        return;
    }
    int cnt = idx.size() / 2, lst = idx[idx.size() - 1 - cnt], ptr = 0;
    bool f = idx.size() & 1;
    string ans = "";
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            if (f && (pos == i || pos == -1 && lst == i)) {
                ans += '1';
            } else if (ptr >= cnt + f)
                ans += '2';
            ptr++;
        } else {
            ans += s[i];
        }
    }
    cout << ans << endl;
}
```

# F 小红的提拉米苏配方 （hard）

显然我们要尽可能把 $0$ 往左移。我们可以删掉当前 $0$ 和左边最近的 $2$ 之间的 $1$ ，把最右边的 $1$ 变成 $2$ 。

用双指针来记录左边要删除的 $1$ ，右边要变成 $2$ 的 $1$ ，动态更新左边最近的 $2$ 。

```cpp
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> idx;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1')
            idx.pb(i);
    }
    vector<int> mark(n);
    int l = 0, r = idx.size() - 1, lst = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '2') {
            lst = i;
        } else if (s[i] == '0') {
            while (l <= r && idx[l] < lst) {
                l++;
            }

            while (l <= r && idx[l] < i) {
                if (idx[r] < i) {
                    break;
                }

                mark[idx[l]] = 1;
                mark[idx[r]] = 2;

                l++;
                r--;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (mark[i] == 1)
            continue;
        if (mark[i] == 2)
            cout << '2';
        else
            cout << s[i];
    }
    cout << endl;
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

