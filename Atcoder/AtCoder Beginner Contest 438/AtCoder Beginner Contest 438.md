# A First Contest of the Year

比赛每 $\text{7}$ 天一次，已知本年第一次比赛在第 $\text{F}$ 天，下一年相当于把日期整体往前平移 $D \mod 7$  天。

```cpp
void solve() {
    int a, b;
    cin >> a >> b;

    int c = b - a % 7;

    if (c <= 0) {
        c += 7;
    }

    cout << c << endl;
}
```

# B Substring 2

假设：

- 当前 $T[j] = a$
- 目标字符（来自 $S$ ）是 `b`

那么把 $a$ 变成 $b$ 的最少操作次数是：

$$(b - a + 10) \bmod 10$$

所以枚举 $S$ 中所有长度为 $M$ 的子串起点 $i$ ，假设 $T$ 要变成 $S[i ... i+M-1]$ ，对每一位 $j$ ，计算把 $T[j]$ 变成 $S[i+j]$ 的最小操作数，累加得到该对齐方式的总操作数，在所有对齐方式中取最小值即可。

```cpp
void solve() {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;

    int ans = inf;

    for (int i = 0; i + m <= n; i++) {
        int c = 0;
        for (int j = 0; j < m; j++) {
            c += (s[i + j] - t[j] + 10) % 10;
        }
        ans = min(ans, c);
    }

    cout << ans << endl;
}
```

# C 1D puyopuyo

从左到右处理序列，并维护一个栈，栈中存放（值，次数）的二元组，表示当前压缩后的序列（连续相同元素及其出现次数）。

当读到一个元素 $x$ 时：

- 如果栈为空，或者栈顶的值 $\neq x$ ，则将 $(x, \text{1})$ 入栈。
- 否则，将栈顶的次数加 $\text{1} $；如果次数变为 $\text{4}$ ，则删除这一整块（将其出栈）。

在弹出一块之后，后续读取的元素（或在弹出后已经处理过的元素）如果与新的栈顶值相同，会被正确地合并。

最终，最小可能的结果长度等于栈中所有剩余次数之和。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<PII> st;
    for (int x : a) {
        if (st.empty() || st.back().fi != x) {
            st.emplace_back(x, 1);
        } else {
            st.back().se++;
            if (st.back().se == 4) {
                st.pop_back();
            }
        }
    }

    ll ans = 0;
    for (auto [_, v] : st) {
        ans += v;
    }

    cout << ans << endl;
}
```

# D Tail of Snake

对每个 $y (2 \leq y \leq N-1)$ ：

- $x$ 必须满足 $1 \leq x < y$
- 我们需要最大化 $sa[x] - sa[x]$

因此只需要维护一个变量 $best$ 表示当前 $y$ 之前的最大 $sa[x] - sb[x]$ 。

```cpp
void solve() {
    int n;
    cin >> n;

    vector<ll> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        cin >> c[i];

    vector<ll> sa(n + 1), sb(n + 1), sc(n + 1);
    for (int i = 1; i <= n; i++) {
        sa[i] = sa[i - 1] + a[i];
        sb[i] = sb[i - 1] + b[i];
        sc[i] = sc[i - 1] + c[i];
    }

    ll S = sa[1] - sb[1];
    ll ans = -INF;

    for (int y = 2; y <= n - 1; y++) {
        ans = max(ans, S + (sb[y] - sc[y]));
        S = max(S, sa[y] - sb[y]);
    }

    ans += sc[n];
    cout << ans << endl;
}
```

# E Heavy Buckets

对每个桶，从初始持有人开始，每次操作在传递前会把当前持有人编号加到桶里，然后桶被传到下一个持有人。令序列 $p_0=v$ （初始持有人），$p_{t+1}=A_{p_t}$ ​​。则经过 $T$ 次操作后，桶中的水量就是

$$\sum\limits_{t=0}^{T-1} p_t.$$

- 设 $up[k][v]$ 为从 $v$ 出发走 $2^k$ 步后的节点（即 $p_{2^k}$ ）。
- 设 $sum[k][v]$ 为从 $v$ 出发的前 $2^k$ 个节点值之和（即 $\sum\limits_{t=0}^{2^k-1} p_t$ 。

初始化 $up[0][v] = A[v]$ , $sum[0][v] = v$（因为 $2^0=1$ ，只包含当前节点 $v$ ）。然后用常规倍增转移：

```
up[k+1][v] = up[k][up[k][v]]
sum[k+1][v] = sum[k][v] + sum[k][up[k][v]]
```

对每个查询，将 $T$ 按二进制展开，从低位到高位依次如果对应位为 $\text{1}$ ，就把 $sum[k][cur]$ 加到答案并令 $cur = up[k][cur]$ 。

```cpp
constexpr int K = 31;
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> up(K, vector<int>(n + 1));
    vector<vector<ll>> sum(K, vector<ll>(n + 1));

    for (int i = 1; i <= n; ++i) {
        up[0][i] = a[i];
        sum[0][i] = i;
    }
    for (int k = 0; k + 1 < K; ++k) {
        for (int i = 1; i <= n; ++i) {
            int mid = up[k][i];
            up[k + 1][i] = up[k][mid];
            sum[k + 1][i] = sum[k][i] + sum[k][mid];
        }
    }

    while (q--) {
        ll t;
        int b;
        cin >> t >> b;
        ll ans = 0;
        int cur = b;
        for (int i = 0; i < K; ++i) {
            if ((t >> i) & 1ll) {
                ans += sum[i][cur];
                cur = up[i][cur];
            }
        }
        cout << ans << endl;
    }
}
```

# F Sum of Mex

- 覆盖 $S_t$ 的最小连通子树 $H_t$ 若不是一条简单路径，则不存在路径能覆盖全部 $S_t$ ，因此 $g(t)=0$ 。
- 若 $H_t$ 是一条路径，设端点为 $L,R$ 。
  - 当 $|H_t|=1$ ：删除该点后，统计跨不同连通块的点对并加上自对，得 $g(t)$ 。
  - 当 $|H_t|\ge2$ ：只有当路径两端分别落在端点两侧的连通块中时，路径才覆盖整条 $H_t$ ，因此 $g(t)=|C_L|\times|C_R|$ 。

用 $\text{LCA}$ 支持距离与“路径第 $k$ 个点”查询。递增加入点 $t-1$ ，用三点间距离更新 $H_t$ 的端点 $L,R$ ，并用 $(d(L,u)+d(R,u)-d(L,R))/2$ 更新节点数。用子树大小计算切边后的连通块大小。

```cpp

    int n;
    cin >> n;
    LCA lca(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        lca.add_edge(u + 1, v + 1);
    }
    lca.build(1);

    vector<int> p = lca.parent, sub(n + 1);
    vector<int> ord = {1};
    for (int i = 0; i < (int)ord.size(); i++) {
        int u = ord[i];
        for (int v : lca.adj[u])
            if (v != p[u])
                ord.push_back(v);
    }
    for (int i = n - 1; i >= 0; i--) {
        int u = ord[i];
        sub[u] = 1;
        for (int v : lca.adj[u])
            if (v != p[u])
                sub[u] += sub[v];
    }

    auto comp = [&](int a, int b) {
        if (p[b] == a)
            return (ll)n - sub[b];
        if (p[a] == b)
            return (ll)sub[a];
        return (ll)sub[a];
    };

    ll ans = 0;
    int L = 1, R = 1;
    ll m = 1;

    for (int t = 1; t <= n; t++) {
        if (m == 1) {
            int v = L;
            ll s = 0;
            for (int to : lca.adj[v]) {
                ll x = (p[to] == v ? sub[to] : n - sub[v]);
                s += x * (x - 1) / 2;
            }
            ans += (ll)n * (n - 1) / 2 - s + 1;
        } else {
            int d = lca.dist(L, R);
            if (m == d + 1) {
                int nl = lca.kth_on_path(L, R, 1);
                int nr = lca.kth_on_path(R, L, 1);
                ans += comp(L, nl) * comp(R, nr);
            }
        }
        if (t == n)
            break;
        int u = t + 1;
        int dLR = lca.dist(L, R);
        int dLu = lca.dist(L, u);
        int dRu = lca.dist(R, u);
        int nL = L, nR = R;
        if (dLu >= dRu && dLu >= dLR) {
            nL = L;
            nR = u;
        } else if (dRu >= dLu && dRu >= dLR) {
            nL = R;
            nR = u;
        }
        int add = (dLu + dRu - dLR) / 2;
        L = nL;
        R = nR;
        m += add;
    }

    cout << ans << "\n";
}
```

# G Sum of Min

利用性质 $i(\mod N)\equiv i(\mod M)(\mod \gcd⁡(N,M))$ ，按照 $r=i(\mod \gcd(N,M))$ 将原问题分解为 $g=\gcd(N,M)$ 个独立的子问题。

在每个子问题中，序列长度变为 $N′=N/g$ 和 $M′=M/g$ ，且 $gcd(N′,M′)=1$ 。

由于互质，子问题在长度 $N′\times M′$ 的周期内会遍历所有 $(A_x′,B_y′)$ 组合。

总项数 $K$ 分解为两部分：

- 完整周期：包含若干个完整的 $N′\times M′$ 矩形，贡献为 $\text{周期数}\times \sum\limits_{x,y}min(A_x′,B_y′)$ 。
- 剩余部分：不足一个周期的部分。对于固定的 $B_y′$ ，其匹配的 $A′$ 下标在模 $N′$ 意义下构成等差数列。

构造新数组 $X$，使得 $X_k=A_{(k⋅M′)\pmod N′}′$ 。这样，原序列中 $A′$ 的“等差数列”访问就变成了 $X$ 上的连续区间访问。

问题转化为：给定数组 $X$ 和数值 $V$ (来自 $B′$)，求区间 $[L,R]$ 上 $\sum min(X_i,V)$ 。

将 $min(X_i,V)$ 拆解为：

- 若 $X_i<V$ ，贡献 $X_i$ 。
- 若 $Xi\geq V$ ，贡献 $V$ 。

将查询按 $V$ 从小到大排序，将 $X$ 元素也排序。使用双树状数组（一个维护个数，一个维护数值和）：

- 随着 $V$ 增大，动态将 $<V$ 的 $X_i$ 加入树状数组。
- 区间答案 $=query\_sum(L,R)+V\times (len−query\_cnt(L,R))$ 。

```cpp
struct Query {
    int id, val, l, r;
    ll weight;
};

struct Event {
    int val, idx;
};

void solve() {
    ll n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n), B(m);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> B[i];

    ll g = __gcd(n, m);
    Z ans = 0;

    vector<int> X;
    vector<Query> qs;
    vector<Event> events;

    for (int r = 0; r < g; r++) {
        if (k <= r)
            break;
        ll limit = (k - 1 - r) / g + 1;

        ll n_ = n / g;
        ll m_ = m / g;

        ll fc = limit / (n_ * m_);
        ll rem = limit % (n_ * m_);

        X.resize(n_);
        for (int t = 0; t < n_; t++) {
            ll idx = ((ll)t * m_) % n_ * g + r;
            X[t] = a[idx];
        }

        qs.clear();

        if (fc > 0) {
            for (int y = 0; y < m_; y++) {
                qs.pb({-1, B[y * g + r], 0, n_ - 1, fc});
            }
        }

        if (rem > 0) {
            ll invm = inv(m_, n_);
            for (int y = 0; y < m_; y++) {
                if (rem - 1 - y < 0)
                    continue;
                ll count = (rem - 1 - y) / m_ + 1;

                int st = ((ll)y * invm) % n_;
                int end = (st + count - 1) % n_;

                if (st <= end) {
                    qs.pb({-1, B[y * g + r], st, end, 1});
                } else {
                    qs.pb({-1, B[y * g + r], st, n_ - 1, 1});
                    qs.pb({-1, B[y * g + r], 0, end, 1});
                }
            }
        }

        if (qs.empty())
            continue;

        events.resize(n_);
        for (int i = 0; i < n_; i++) {
            events[i] = {X[i], i};
        }

        sort(all(qs), [&](Query a, Query b) { return a.val < b.val; });
        sort(all(events), [&](Event a, Event b) { return a.val < b.val; });

        BIT<int> tc(n_);
        BIT<Z> ts(n_);

        int ptr = 0;
        for (auto q : qs) {
            while (ptr < n_ && events[ptr].val < q.val) {
                tc.add(events[ptr].idx + 1, 1);
                ts.add(events[ptr].idx + 1, Z(events[ptr].val));
                ptr++;
            }

            int cnt = tc.ask(q.l + 1, q.r + 1);
            Z sum = ts.ask(q.l + 1, q.r + 1);
            int len = q.r - q.l + 1;

            Z cur = sum + Z(q.val) * Z(len - cnt);
            ans += cur * Z(q.weight);
        }
    }

    cout << ans << endl;
}
```

# 头文件

```cpp
#include<bits/stdc++.h>
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

# 树状数组

```cpp
template<class Int>
struct BIT {
    vector<Int> a;
    int n;

    BIT() {}
    BIT(int n) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        a.resize(n + 1);
    }

    void add(int x, Int k) {
        for (; x <= n; x += x & -x) {
            a[x] += k;
        }
    }

    void add(int x, int y, Int k) {
        add(x, k), add(y + 1, -k);
    }

    Int ask(int x) {
        Int ans = 0;
        for (; x; x -= x & -x) {
            ans += a[x];
        }
        return ans;
    }

    Int ask(int x, int y) {
        return ask(y) - ask(x - 1);
    }

    Int kth(int k) {
        Int ans = 0;
        for (int i = __lg(n); i >= 0; i--) {
            Int val = ans + (1 << i);
            if (val < n && a[val] < k) {
                k -= a[val];
                ans = val;
            }
        }
        return ans + 1;
    }
};
```

# 自动取模

```cpp
template<class T>
constexpr T ksm(T a, ll b) {
	T res = 1;
	while (b) {
		if (b & 1) res *= a;
		b >>= 1;
		a *= a;
	}
	return res;
}

template<int P>
struct MInt {
	int x;
	constexpr MInt(): x() {}
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

template<>
int MInt<0>::Mod = 998244353;

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

using Z = MInt<MOD>;
```

# 扩欧求逆元

```cpp
template <class T> T sign(const T &a) { return a == 0 ? 0 : (a < 0 ? -1 : 1); }
template <class T> T ceil(const T &a, const T &b) {
    T A = abs(a), B = abs(b);
    assert(b != 0);
    return sign(a) * sign(b) > 0 ? (A + B - 1) / B : -A / B;
}
template <class T> T exgcd(T a, T b, T &x, T &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    T d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

template <class T> T inv(T a, T m) {
    T x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}
```

# 倍增 LCA

```cpp
struct LCA {
    int n, LOG;
    vector<vector<int>> up;
    vector<int> dep, parent;
    vector<vector<int>> adj;
    LCA(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        LOG = 1;
        while ((1 << LOG) <= max(1, n))
            ++LOG;
        up.assign(LOG, vector<int>(n + 1, 0));
        dep.assign(n + 1, 0);
        parent.assign(n + 1, 0);
        adj.assign(n + 1, {});
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void build(int root = 1) {
        vector<int> order;
        order.reserve(n);
        order.push_back(root);
        parent[root] = 0;
        dep[root] = 0;
        for (size_t i = 0; i < order.size(); ++i) {
            int u = order[i];
            for (int v : adj[u])
                if (v != parent[u]) {
                    parent[v] = u;
                    dep[v] = dep[u] + 1;
                    order.push_back(v);
                }
        }
        for (int v = 1; v <= n; ++v)
            up[0][v] = parent[v] == 0 ? v : parent[v];
        for (int k = 1; k < LOG; ++k) {
            for (int v = 1; v <= n; ++v)
                up[k][v] = up[k - 1][up[k - 1][v]];
        }
    }
    int kth_up(int u, int k) {
        int cur = u;
        for (int b = 0; b < LOG; ++b)
            if ((k >> b) & 1)
                cur = up[b][cur];
        return cur;
    }
    int lca(int x, int y) {
        if (dep[x] < dep[y])
            swap(x, y);
        int diff = dep[x] - dep[y];
        x = kth_up(x, diff);
        if (x == y)
            return x;
        for (int k = LOG - 1; k >= 0; --k) {
            if (up[k][x] != up[k][y]) {
                x = up[k][x];
                y = up[k][y];
            }
        }
        return up[0][x];
    }
    int dist(int x, int y) {
        int c = lca(x, y);
        return dep[x] + dep[y] - 2 * dep[c];
    }
    int kth_on_path(int u, int v, int k) {
        int c = lca(u, v);
        int du = dep[u] - dep[c];
        if (k <= du) {
            return kth_up(u, k);
        } else {
            int rem = k - du;
            int dv = dep[v] - dep[c];
            int steps_up = dv - rem;
            return kth_up(v, steps_up);
        }
    }
};
```