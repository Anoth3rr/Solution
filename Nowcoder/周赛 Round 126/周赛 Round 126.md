# A 小红的顺子构造

构造以 $x-4$ 为首的顺子即可，如果 $x-4<1$ ，就以 $\text{1}$ 为首。

```cpp
void solve() {
    int x;
    cin >> x;
    int l = max(x - 4, 1);
    for (int i = l; i <= l + 4; ++i)
        cout << i << " ";
    cout << endl;
}
```

# B 小红的字符串构造（easy）

因为保证两两有前缀关系。排序一遍，如果第 $k$ 个字符串是前缀，那么前 $k-1$ 个字符串同样是前缀。所以我们需要检查第 $k$ 个和第 $k+1$ 个，如果二者相等，那么当满足第 $k$ 个是前缀时，必然满足第 $k+1$ 个也是前缀，于是无法构造。

```cpp
void solve() {
    int n, k;
    cin >> n >> k;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(all(a));
    if (k == n) {
        cout << a[n - 1] << endl;
    } else {
        if (a[k - 1].size() == a[k].size()) {
            cout << -1 << endl;
        } else {
            cout << a[k - 1] << endl;
        }
    }
}
```

# C 小红的好数组构造

如果 $n-k$ 为奇数，删去 $k$ 个字符后剩余的字符中，肯定有一个字符出现了奇数次。

剩余的情况，我们可以构造 $k$ 个不同的数字 $\text{+}$ $n-k$ 个 $\text{1}$ 。

```cpp
void solve() {
    int n, k;
    cin >> n >> k;
    if ((n - k) & 1) {
        cout << -1 << endl;
        return;
    }
    for (int i = 2; i <= k + 1; ++i)
        cout << i << " ";
    for (int i = 0; i < n - k; ++i)
        cout << 1 << " ";
    cout << endl;
}
```

# D 小红的左看右看构造

先检查 $c$ 和 $d$ 的最后一个元素是否相等，这个是数组的最大值。

我们从左到右直接放 $c$ 的前 $x-1$ 个元素，从右到左直接放 $d$ 的前 $y-1$ 个元素，中间放最后一个元素，剩下的空位随便放小的数字即可。

注意这种构造方式至少需要 $x+y-1$ 个元素。

```cpp
void solve() {
    int x, y, n;
    cin >> x >> y >> n;
    int c, d;
    vector<int> ans(n);
    for (int i = 0, t; i < x; ++i) {
        cin >> t;
        if (i < x - 1)
            ans[i] = t;
        else
            c = t;
    }
    for (int i = 0, t; i < y; ++i) {
        cin >> t;
        if (i < y - 1)
            ans[n - 1 - i] = t;
        else
            d = t;
    }
    if (c != d) {
        cout << -1 << endl;
        return;
    }
    if (x + y - 1 > n) {
        cout << -1 << endl;
        return;
    }
    ans[x - 1] = c;
    int i = x;
    while (!ans[i])
        ans[i++] = 1;
    for (int i = 0; i < n; ++i)
        cout << ans[i] << " ";
    cout << endl;
}
```

# E 小红的完全平方数构造

和 [小白月赛 Round 126 E](https://ac.nowcoder.com/acm/contest/125955/E) 一样的思路。我们只需要找到 $x$ 使得 $n\times 10^L \leq x< (n+1)\times 10^L$ 即可。

```cpp
void solve() {
    ll n;
    cin >> n;
    ll a = 10;
    for (int i = 0; i <= 10; ++i) {
        ll x = n * a;
        ll l = 1, r = 1e9, d = r;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            if (mid * mid >= n * a)
                d = mid, r = mid - 1;
            else
                l = mid + 1;
        }
        if (d * d < (n + 1) * a) {
            cout << d * d << endl;
            return;
        }
        a *= 10;
    }
}
```

# F 小红的基环树染色构造

先利用拓扑排序找环，环我们用 $1212...$ 的方式来染色，如果环的长度为奇数，就再加一个 $3$ 。然后对于环上延伸出去的每棵子树，我们都让子节点与父节点颜色不同即可。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    vector<int> deg(n + 1);
    for (int i = 0; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].pb(v), g[v].pb(u);
        deg[u]++, deg[v]++;
    }

    vector<int> vis(n + 1);
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 1)
            q.push(i);

    while (q.size()) {
        auto u = q.front();
        q.pop();

        vis[u] = 1;
        for (auto v : g[u]) {
            if (deg[v] > 1) {
                deg[v]--;
                if (deg[v] == 1)
                    q.push(v);
            }
        }
    }
    vector<int> cyc;
    int st = 0;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            st = i;
            break;
        }
    }

    int cur = st;
    vector<bool> vis2(n + 1);

    while (1) {
        cyc.pb(cur);
        vis2[cur] = true;

        int nxt = 0;
        for (int v : g[cur]) {
            if (!vis[v] && !vis2[v]) {
                nxt = v;
                break;
            }
        }

        if (nxt != 0) {
            cur = nxt;
        } else {
            break;
        }
    }

    vector<int> a(n + 1);
    int k = cyc.size();
    for (int i = 0; i < k; ++i) {
        int u = cyc[i];
        if (i < k - 1) {
            a[u] = (i % 2) + 1;
        } else {
            for (int c = 1; c <= 3; ++c) {
                if (c != a[cyc[i - 1]] && c != a[cyc[0]]) {
                    a[u] = c;
                    break;
                }
            }
        }
    }

    queue<int> q2;
    for (int u : cyc) {
        q2.push(u);
    }

    while (!q2.empty()) {
        int u = q2.front();
        q2.pop();

        for (int v : g[u]) {
            if (a[v] == 0) {
                for (int c = 1; c <= 3; ++c) {
                    if (c != a[u]) {
                        a[v] = c;
                        break;
                    }
                }
                q2.push(v);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}
```

# G 小红的字符串构造（hard）

构建一棵 $\text{Trie}$ 树，用 $end[i]$ 记录有多少个字符串恰好在此结束，我们只要找到一个节点，使得根节点到它的路径上 $end$ 之和恰好等于 $k$ 即可。

```cpp
void solve() {
    int n, k;
    cin >> n >> k;
    Trie tr(maxn);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        tr.insert(s);
    }

    int tar = tr.find(0, 0, k);

    if (tar != -1) {
        cout << tr.get(tar) << endl;
    } else {
        cout << -1 << endl;
    }
}
```

# 头文件

```cpp
#include <bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define endl "\n"
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using i128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<ll, ll, ll>;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ld eps = 1e-10;

void init() {}

void solve() {}

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

# Trie 树

```cpp
struct Trie {
    vector<array<int, 2>> ch;
    vector<int> end, fa, val;
    int idx = 0;

    Trie(int n) : ch(n), end(n), fa(n), val(n) {}

    void insert(string s) {
        int u = 0;
        for (char c : s) {
            int v = c - '0';
            if (!ch[u][v]) {
                ch[u][v] = ++idx;
                ch[idx][0] = ch[idx][1] = 0;
                end[idx] = 0;
                fa[idx] = u;
                val[idx] = v;
            }
            u = ch[u][v];
        }
        end[u]++;
    }

    int find(int u, int cur, int k) {
        cur += end[u];

        if (cur == k && u != 0) {
            return u;
        }

        if (cur > k) {
            return -1;
        }

        for (int v = 0; v < 2; ++v) {
            if (ch[u][v]) {
                int res = find(ch[u][v], cur, k);
                if (res != -1)
                    return res;
            }
        }

        return -1;
    }
    string get(int u) {
        string res = "";
        while (u > 0) {
            res += to_string(val[u]);
            u = fa[u];
        }
        reverse(all(res));
        return res;
    }
};
```

