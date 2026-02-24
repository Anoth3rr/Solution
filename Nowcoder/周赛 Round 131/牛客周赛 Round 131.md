先提前祝大家新年快乐

# A ICPC Balloons

判一下就行

```cpp
void solve() {
    string s;
    cin >> s;
    if (s == "A")
        cout << "red" << endl;
    if (s == "B")
        cout << "orange" << endl;
    if (s == "C")
        cout << "blue" << endl;
    if (s == "D")
        cout << "green" << endl;
}
```

# B String Covering

不难发现，只有单个 $1$ 是染不出来的。

```cpp
void solve() {
    int n;
    string s;
    cin >> n >> s;
    int cnt = 0;
    for (auto v : s) {
        if (v == '1')
            cnt++;
        else {
            if (cnt == 1) {
                cout << "NO" << endl;
                return;
            }
            cnt = 0;
        }
    }
    if (cnt == 1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
}
```

# C Get The Sequence

贪心匹配即可，如果 $a[i]>b[ptr]$ ，就匹配上了，否则换下一个 $a[i+1]$ 继续匹配。

```cpp
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < m; ++i)
        cin >> b[i];
    int ptr = 0;
    for (int i = 0; i < n; ++i) {
        if (ptr == m)
            break;
        if (a[i] >= b[ptr]) {
            ptr++;
        }
    }
    if (ptr == m)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
```

# D Longest Subsequence

也就是求最长子序列，我们用 $dp[x]$ 记录以 $x$ 为结尾的最长子序列长度，它只能从 $x-1$ 或 $x+1$ 演变过来，显然有
$$
dp[x] = \max(dp[x],\max(dp[x-1],dp[x+1])+1)
$$

```cpp
void solve() {
    int n;
    cin >> n;
    unordered_map<int, int> dp;
    int ans = 0;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        dp[x] = max(dp[x], max(dp[x - 1], dp[x + 1]) + 1);
        ans = max(ans, dp[x]);
    }
    cout << ans << endl;
}
```

# E Eat The Candy

一个盒子的糖果参与了合并，对于这个盒子一定是不优的（最优的情况也就是拿出一个合并，然后获取一个新产生的糖果）。所以显然合并出来的新糖放到同一个盒子里是最优的，且那个盒子不能进行合并。合并可以从两边向中间贪心匹配（两边向中间能合并就合并），也就是如果最后第 $i$ 个盒子糖果最多，就是它原本的糖果数 $+$ 左边新生成的糖果数 $+$ 右边新生成的糖果数。

左边的糖果数在枚举过程中动态计算即可，右边的可以用一个后缀数组预先算好。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    vector<ll> suf(n + 2);

    ll rem = a[n];
    for (int i = n - 1; i >= 1; --i) {
        ll ops = min(a[i], rem);
        suf[i] = suf[i + 1] + ops;
        rem = a[i] - ops;
    }

    ll ans = 0, S = 0;
    rem = 0;
    for (int i = 1; i <= n; ++i) {
        ll cur = a[i] + S + suf[i + 1];
        if (cur > ans)
            ans = cur;
        ll ops = min(rem, a[i]);
        S += ops;
        rem = a[i] - ops;
    }
    cout << ans << endl;
}
```

# F Bracket Coloring

两个典题揉一块造出来的典题。

先是括号匹配，直接用栈模拟一下即可。如果把每一组括号看成一个节点，那么如果相邻两个字符相同，他们所属的节点之间就要连一条边，然后你就会发现，我趣，原来是无向图的 $2$ 色染色问题。

那么每一个连通分量都有两种染色方式，答案就是 $2^{\text{连通分量个数}}$ 。

因为我是超级懒狗，所以直接用 $\text{DSU}$ 维护了（你用其他方式求连通分量都是可以的）。

```cpp
void solve() {
    int n;
    string s;
    cin >> n >> s;
    vector<int> pid(n), stk;
    int id = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(')
            stk.pb(i);
        else {
            int l = stk.back();
            stk.pob();
            ++id;
            pid[l] = pid[i] = id;
        }
    }
    DSU dsu(id);
    for (int i = 0; i + 1 < n; i++) {
        if (s[i] == s[i + 1]) {
            int u = pid[i], v = pid[i + 1];
            if (u != v)
                dsu.merge(u, v);
        }
    }

    vector<bool> vis(id + 1);
    int c = 0;
    for (int i = 1; i <= id; i++) {
        int rt = dsu.find(i);
        if (!vis[rt]) {
            vis[rt] = 1;
            c++;
        }
    }
    cout << ksm(Z(2), c) << endl;
}
```