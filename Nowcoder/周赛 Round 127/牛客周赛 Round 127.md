# A Get The Number

$c=a\div b$ 等价于 $b\times c=a$ ，这样就不需要判断是否整除。

```cpp
void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    if (c == a + b || c == a - b || c == a * b || b * c == a) cout << "YES" << endl;
    else cout << "NO" << endl;
}
```

# B Sudoku

一个很简单但是写起来比较不优雅的题目，这里给出一种相对比较优雅的解法。

对于每个数字，记录它的行，列，宫信息，检查是否有重复。

```cpp
void solve() {
    int n = 4;
    unordered_set<string> st1, st2, st3;
    bool f = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0, x; j < n; ++j) {
            cin >> x;
            string s1 = to_string(i) + "#" + to_string(x);
            string s2 = to_string(j) + "#" + to_string(x);
            string s3 = to_string(i / 2 * 2 + j / 2) + "#" + to_string(x);
            if (st1.count(s1) || st2.count(s2) || st3.count(s3)) {
                f = 0;
            }
            st1.insert(s1);
            st2.insert(s2);
            st3.insert(s3);
        }
    }
    cout << (f ? "YES" : "NO") << endl;
}
```



# C Carry The Bit

显然越靠左的位置进位，越靠右的位置舍位是最优的。

- 特判第一位大于 $5$ ，此时数字变为 $100...$ 
- 如果当前位 $<5$ ，那么我们就保留前一位

- 如果当前位 $\geq 5$ ，前一位 $+1$ ，后面所有数字都改为 $0$ 。

```cpp
void solve() {
    string s;
    cin >> s;
    bool f = 0;
    string ans = "";
    if (s[0] >= '5') {
        cout << 1 << string(s.size(), '0') << endl;
        return;
    }
    for (int i = 1; i < s.size(); ++i) {
        if (!f && s[i] >= '5') ans += s[i - 1] + 1, f = 1;
        else if (f) ans += '0';
        else ans += s[i - 1];
    }
    ans += '0';
    cout << ans << endl;
}
```

# D Permutation² Counting

我们要计算的排列即为 $\text{\{1,1\},\{1,1,2,2\},\{1,1,2,2,3,3\}...}$ 。

先预存每个数字出现的次数。枚举 $i\in [1,n/2]$ （因为最多这些有效），如果 $i$ 出现的次数 $<2$ ，那么这个数字及以后（数值上）的所有数字都选不了。

如果这个数字 $x$ 可以选（出现的次数 $\geq 2$ ），那么当前的排列 $\text{\{1,1,2,2,...,x-1,x-1\}}$ 就能拓展出 $\binom{cnt[x]}{2}$ 中选择，对每个双排列的个数求和即可。

```cpp
void solve() {
    int n;
    cin >> n;
    unordered_map<int, Z> mp;
    for (int i = 0, x; i < n; ++i) cin >> x, mp[x] += 1;
    Z ans = 0, S = 1;
    for (int i = 1; i <= n; ++i) {
        if (mp[i].val() < 2) break;
        S *= mp[i] * (mp[i] - 1) / 2;
        ans += S;
    }
    cout << ans << endl;
}
```

# E Balanced 01-String

令相邻不同的对数为 $T$ ，相邻相同的对数为 $S$ ，有
$$
S+T=n-1
$$

$$
T\pmod 2 = \sum_1^{n-1}(b[i]\ne b[i+1])\pmod 2 = \bigoplus_1^{n-1}(b[i]\oplus[i+1]) = b[1]\oplus b[n]
$$

所以只需要满足：
$$
T\equiv n-1\pmod2
$$
剩下的位置可以随便填。

```cpp
void solve() {
    string s;
    cin >> s;
    int n = s.size(), cnt = 0;
    for (auto v : s) if (v == '?') cnt++;
    if (n == 1) {
        cout << ksm(Z(2), cnt) << endl;
        return;
    }
    char a = s.front(), b = s.back();
    if (a != '?' && b != '?') {
        if ((a ^ b) == !(n & 1)) cout << ksm(Z(2), cnt) << endl;
        else cout << 0 << endl;
    } else {
        cout << ksm(Z(2), cnt - 1) << endl;
    }
}
```

# F Matrix Coloring

对于任意白格，检查其 $\text{4-}$方向（上下左右）的黑色邻居：

- $\geq 3$ 个黑邻居：根据鸽巢原理，必有一对邻居呈 $\text{90}$ 度相邻，它们在 $\text{8-}$ 方向直接连通，故该白格必变黑。

- $2$ 个黑邻居：
  - $\text{90}$度相邻：直接 $\text{8-}$ 方向连通 $\rightarrow$ 变黑。
  - $\text{180}$ 度相对：检查它们在 $\text{DSU}$ 中是否连通。
    - 若连通 $\rightarrow$ 变黑；
    - 若不连通，加入这两个分量的等待列表。

当一个白格变黑时，将其加入队列。处理队列时，将新黑格与周围 $\text{8-}$ 邻居的黑格在 $\text{DSU}$ 中合并。合并两个连通块时，检查较小块的等待列表中的白格，看合并后它们是否满足了连通条件（启发式合并，保证效率）。最后，更新新黑格周围 $\text{4-}$ 邻居白格的状态。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (int i = 0; i < n; ++i) cin >> g[i];

    DSU dsu(n * n);
    vector<vector<int>> w(n * n);
    queue<int> q;

    auto id = [&](int x, int y) { return x * n + y; };
    auto check = [&](int x, int y) { return 0 <= x && x < n && 0 <= y && y < n; };

    auto chk = [&](int u) {
        if (g[u / n][u % n] == '1') return;
        int x = u / n, y = u % n;
        vector<int> b;
        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k * 2 + 1], ny = y + dy[k * 2 + 1];
            if (check(nx, ny) && g[nx][ny] == '1') b.pb(id(nx, ny));
        }

        bool f = true;
        if (b.size() >= 3) {
            f = false;
        } else if (b.size() == 2) {
            int x = b[0], y = b[1];
            bool ff = (abs(x / n - y / n) == 2 || abs(x % n - y % n) == 2);
            if (!ff || dsu.same(x, y)) {
                f = false;
            } else {
                w[dsu.find(x)].pb(u);
                w[dsu.find(y)].pb(u);
            }
        }

        if (!f) {
            g[x][y] = '1';
            q.push(u);
        }
    };

    auto unite = [&](int x, int y) {
        x = dsu.find(x);
        y = dsu.find(y);
        if (x == y) return;
        if (dsu.siz[x] < dsu.siz[y]) swap(x, y);
        dsu.f[y] = x;
        dsu.siz[x] += dsu.siz[y];

        for (int u : w[y]) chk(u);
        vector<int>().swap(w[y]);
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == '1') {
                int u = id(i, j);
                for (int k = 0; k < 8; ++k) {
                    int ni = i + dx[k], nj = j + dy[k];
                    if (check(ni, nj) && g[ni][nj] == '1') unite(u, id(ni, nj));
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == '0') chk(id(i, j));
        }
    }

    while (q.size()) {
        int u = q.front();
        q.pop();
        int x = u / n, y = u % n;
        for (int k = 0; k < 8; ++k) {
            int nx = x + dx[k], ny = y + dy[k];
            if (check(nx, ny) && g[nx][ny] == '1') unite(u, id(nx, ny));
        }

        for (int k = 0; k < 4; ++k) {
            int nx = x + dx[k * 2 + 1], ny = y + dy[k * 2 + 1];
            if (check(nx, ny) && g[nx][ny] == '0') chk(id(nx, ny));
        }
    }

    for (auto s : g) cout << s << endl;
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

# 并查集

```cpp
struct DSU {
    vector<int> f, siz;

    DSU() {}
    DSU(int n) {
        init(n);
    }

    void init(int n) {
        f.resize(n + 1);
        iota(f.begin(), f.end(), 0);
        siz.assign(n + 1, 1);
    }

    int find(int x) {
        return f[x] == x ? x : f[x] = find(f[x]);
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        f[y] = x;
        siz[x] += siz[y];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return siz[find(x)];
    }
};
```

