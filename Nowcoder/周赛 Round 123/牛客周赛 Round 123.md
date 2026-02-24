# A 小红玩牌

字符直接进行比较，比的是 $\text{ASCII}$ 码。

```cpp
void solve() {
    int n1, n2;
    char c1, c2;
    cin >> n1 >> c1 >> n2 >> c2;
    if (n1 != n2) cout << (n1 > n2 ? "Yes" : "No") << endl;
    else cout << (c1 < c2 ? "Yes" : "No") << endl;
}
```

# B 小红作弊

检查每一个花色牌的数量，每一次操作可以使多的 $\text{-1}$ ，少的 ${+1}$ ，所以差值 $\div 2$ 就是操作次数。

```cpp
void solve() {
    vector<int> a(13);
    int ans = 0;
    for (int i = 0; i < 13; ++i) cin >> a[i];
    for (int i = 0, x; i < 13; ++i) cin >> x, ans += abs(a[i] + x - 4);
    cout << ans / 2 << endl;
}
```

# C 小红出对

不能打出两张花色与牌面数字都相同的牌，所以我们先对牌去重，对于每个花色，把牌两两组合输出即可。

```cpp
void solve() {
    int n;
    cin >> n;
    unordered_map<int, unordered_map<char, int>> g;

    for (int i = 1; i <= n; i++) {
        int x;
        char c;
        cin >> x >> c;
        if (!g[x][c]) g[x][c] = i;
    }

    vector<PII> ans;

    for (auto v : g) {
        vector<int> vec;
        for (auto q : v.se) vec.pb(q.se);

        for (int i = 0; i + 1 < vec.size(); i += 2) ans.eb(vec[i], vec[i + 1]);
    }

    cout << ans.size() * 2 << endl;
    for (auto [u, v] : ans) cout << u << " " << v << endl;
}
```

# D 小红打牌

限制更大的显然是连续的两个三连对，所以我们可以枚举这样的三连对，剩下的两个对子可以用两个不同的对子组成，也可以用四张相同的牌组成，动态维护张数 $\geq 2$ 和张数 $\geq 4$ 的点数即可。

```cpp
void solve() {
    int n;
    cin >> n;
    unordered_map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    ll tot2 = 0, tot4 = 0;
    for (auto [u, v] : cnt) tot2 += v >= 2, tot4 += v >= 4;

    auto update = [&](int x, int d) {
        if (cnt[x] >= 2) tot2--;
        if (cnt[x] >= 4) tot4--;

        cnt[x] += d;

        if (cnt[x] >= 2) tot2++;
        if (cnt[x] >= 4) tot4++;
    };

    ll ans = 0;
    for (auto [u, v] : cnt) {
        if (v >= 3 && cnt[u + 1] >= 3) {
            update(u, -3);
            update(u + 1, -3);

            if (tot2 >= 2) {
                ans = (ans + tot2 * (tot2 - 1) / 2) % MOD;
            }

            if (tot4 > 0) {
                ans = (ans + tot4) % MOD;
            }

            update(u, 3);
            update(u + 1, 3);
        }
    }
    cout << ans << endl;
}
```

# E/F 小红出牌

因为需要回答 $x\in[1,n]$ 的每个答案，所以我们考虑引入一张新的牌时会有哪些变化。

设新引入的牌为 $x$ ，对于点数 $t$ ，已经有了 $cnt[t]$ 张牌：

- 如果原来有 $cnt[x] < cnt[x-1]$ ，我们可以把 $x$ 接在其中某一条以 $x-1$ 结尾的顺子上，数量不变。

- 如果原来有 $cnt[x]\geq cnt[x-1]$ ，那么就没有可以接的顺子了，所以我们要新开一条， $ans + 1$ 。

- 如果原来有 $cnt[x]<cnt[x+1]$ ，我们可以把多余的以 $x+1$ 为始的顺子连到新的 $x$ 上，相当于少了一条以 $x+1$ 为始的顺子， $ans-1$ 。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> cnt(n + 2);
    int ans = 0;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        if (cnt[x] >= cnt[x - 1]) ans++;
        if (cnt[x + 1] > cnt[x]) ans--;
        cnt[x]++;
        cout << ans << " ";
    }
}
```

# G 小红出千

最后的目标序列是 $[s,s+n-1]$ ，所以我们只需要找到一个 $s$ ，使得这个区间内的不同值个数最大即可。

当然从 $\text{1}$ 到 $10^9$ 枚举 $s$ 肯定会超时。我们发现，随着 $s$ 在两个相邻不同原值之间移动，能落入区间 $[s,s+n-1]$ 的不同原值集合不变，只有当 $s$ 跨过某个原值时集合才会变化。所以我们只需考虑这些“断点”。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    unordered_map<int, vector<int>> mp;
    for (int i = 0; i < n; ++i) mp[a[i]].pb(i + 1);

    vector<int> u;
    for (auto p : mp) u.pb(p.fi);
    sort(all(u));

    int m = u.size(), bs = 1, bc = upper_bound(all(u), n) - u.begin();

    int r = 0;
    for (int l = 0; l < m; ++l) {
        if (r < l) r = l;
        int R = u[l] + n - 1;
        while (r < m && u[r] <= R) ++r;
        int cnt = r - l;
        if (cnt > bc) {
            bc = cnt;
            bs = u[l];
        }
    }

    int s = bs, R = s + n - 1;

    unordered_map<int, bool> used;
    vector<bool> keep(n + 1, 0);

    for (int i = s; i <= R; ++i) {
        if (mp.count(i) && !mp[i].empty()) {
            int id = mp[i].back();
            mp[i].pop_back();
            keep[id] = 1;
            used[i] = 1;
        }
    }

    vector<int> need;
    
    vector<int> chg;
    for (int i = s; i <= R; ++i)
        if (!used.count(i)) need.pb(i);

    for (int i = 1; i <= n; ++i)
        if (!keep[i]) chg.pb(i);

    cout << chg.size() << endl;
    for (int i = 0; i < chg.size(); ++i) cout << chg[i] << " " << need[i] << endl;
}
```

# 头文件

```cpp
//Another
#include<bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using i128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TLLL = tuple<ll, ll, ll>;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
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

