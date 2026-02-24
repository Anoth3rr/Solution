# A Square?

判断四个值是否相等即可。

```cpp
void solve() {
	int tar;
	bool f = true;
	cin >> tar;
	for (int i = 0, x; i < 3; ++i) {
		cin >> x;
		if (x != tar) f = false;
	}
	if (f) cout << "YES" << "\n";
	else cout << "NO" << "\n";
}
```

# B Your Name

统计字符种类和个数即可。

```cpp
void solve() {
	int n;
	string s;
	vector<int> dic(26);

	cin >> n >> s;
	for (auto v : s) dic[v - 'a']++;
	cin >> s;
	for (auto v : s) dic[v - 'a']--;
	for (auto v : dic) {
		if (v) {
			cout << "NO" << "\n";
			return;
		}
	}
	cout << "YES" << "\n";
}
```

# C Isamatdin and His Magic Wand!

瞪眼法看出，只要有奇偶就可以排序，全奇/全偶则不能。

```
void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	bool f, ok = true;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		if (i == 0) f = a[i] & 1;
		if ((a[i] & 1) != f) ok = false;
	}
	if (ok) {
		for (int i = 0; i < n; ++i) cout << a[i] << " ";
		cout << "\n";
		return;
	}

	sort(all(a));

	for (int i = 0; i < n; ++i) {
		cout << a[i] << " ";
	}

	cout << "\n";
}
```

# D Yet Another Array Problem

因为存在一个数与数组内数字互质即可，可以猜到答案不会很大，暴力验证一下即可。

证明是：

$$2\times3\times5\times7\times11\times13\times17\times19\times23\times29\times31\times37\times41\times43\times47\times53\geq 10^{18}$$

```cpp
int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

void solve() {
	int n;
	cin >> n;
	vector<ll> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	ll ans = -1;
	for (auto p : primes) {
		bool f = false;
		for (int i = 0; i < n; i++) {
			if (a[i] % p != 0) {
				f = true;
				break;
			}
		}
		if (f) {
			ans = p;
			break;
		}
	}
	cout << ans << "\n";
}
```

# E khba Loves to Sleep!

二分最小距离 $m$ 。对于确定的 $m$ ，每个朋友 $a_i$ 会禁止区间 $[a_i-(m-1),\,a_i+(m-1)]$（ 取交到 $[0,x]$ 上 ）；合并这些禁止区间后，允许的整点数量为 $(x+1)−$ 禁止点总数。若允许点数 $\geq k$ ，则 $m$ 可行。

找到最大的 $m$ 后，从允许区间里按从小到大取出 $k$ 个不同整点输出即可。

```cpp
void solve() {
	ll n, k, x;
	cin >> n >> k >> x;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	sort(all(a));

	auto check = [&](ll m)->bool {
		if (m == 0) return true;
		ll r = m - 1;
		vector<PLL> segs;
		for (int i = 0; i < n; ++i) {
			ll L = a[i] - r;
			ll R = a[i] + r;
			if (R < 0 || L > x) continue;
			L = max(L, 0ll);
			R = min(R, x);
			segs.eb(L, R);
		}
		if (segs.empty()) {
			return x + 1 >= k;
		}
		sort(all(segs));
		ll tot = 0, curL = segs[0].fi, curR = segs[0].se;
		for (int i = 1; i < segs.size(); ++i) {
			if (segs[i].fi <= curR + 1) {
				curR = max(curR, segs[i].se);
			} else {
				tot += (curR - curL + 1);
				curL = segs[i].fi;
				curR = segs[i].se;
			}
		}
		tot += (curR - curL + 1);
		return x + 1 - tot >= k;
	};

	ll lo = 0, hi = x + 1;
	while (lo < hi - 1) {
		ll mid = lo + (hi - lo) / 2;
		if (check(mid)) lo = mid;
		else hi = mid;
	}
	ll best = lo;

	vector<ll> ans;
	if (best == 0) {
		for (int i = 0; i < k; ++i) ans.pb(i);
	} else {
		ll r = best - 1;
		vector<PLL> segs;
		for (int i = 0; i < n; ++i) {
			ll L = a[i] - r;
			ll R = a[i] + r;
			if (R < 0 || L > x) continue;
			L = max(L, 0ll);
			R = min(R, x);
			segs.eb(L, R);
		}
		if (segs.empty()) {
			for (ll i = 0; ans.size() < k && i <= x; ++i) ans.pb(i);
		} else {
			sort(all(segs));
			vector<PLL> merged;
			ll curL = segs[0].fi, curR = segs[0].se;
			for (int i = 1; i < segs.size(); ++i) {
				if (segs[i].fi <= curR + 1) curR = max(curR, segs[i].se);
				else {
					merged.eb(curL, curR);
					curL = segs[i].fi;
					curR = segs[i].se;
				}
			}
			merged.eb(curL, curR);

			ll cur = 0;
			for (auto [Lf, Rf] : merged) {
				if (cur <= Lf - 1) {
					for (ll i = cur; i <= Lf - 1 && ans.size() < k; ++i) ans.pb(i);
				}
				cur = Rf + 1;
				if (ans.size() >= k) break;
			}
			for (ll i = cur; i <= x && ans.size() < k; ++i) ans.pb(i);
		}
	}

	while (ans.size() < k) {
		ll p = 0;
		unordered_set<ll> used(all(ans));
		while (ans.size() < k && p <= x) {
			if (!used.count(p)) {
				ans.pb(p);
				used.insert(p);
			}
			++p;
		}
	}

	for (int i = 0; i < k; ++i) {
		cout << ans[i] << " ";
	}
	cout << "\n";
}
```

# F Tree, TREE!!!

对于任意根 $r$ ：

- 某个节点 $v$ 会出现在 $S_r$ 中，当且仅当：
  - $v$ 的子树中至少有 $k$ 个节点（当以 $r$ 为根时）。

因此，我们只需要知道，当根不同的时候，每个节点的“子树大小”如何变化即可。

对于固定的一条边 $(u, v)$ ，如果把这条边断开，整棵树被分成两个部分：

- 一边大小为 $sz[v]$
- 另一边大小为 $n - sz[v]$

当我们选择不同的根时：

- 如果根在 $v$ 的子树内，则 $v$ 的子树大小是 $sz[v]$ ；
- 如果根在另一侧，则 $v$ 的子树大小是 $n - sz[v]$ 。

所以这条边会产生如下贡献：

$$[\text{sz[v]} \ge k] \times (n - \text{sz[v]}) + [n - \text{sz[v]} \ge k] \times \text{sz[v]}$$

解释：

- 若 `sz[v] >= k`，则当根在另一侧的 `(n - sz[v])` 个节点中时，节点 `v` 可被计入；
- 若 `n - sz[v] >= k`，则当根在 `v` 的子树内的 `sz[v]` 个节点中时，节点 `v` 也可被计入。

此外，每个节点作为根时本身也一定能计入一次，因为整个树大小为 `n >= k` ，因此还要额外加上 `n`。

```cpp
void solve() {
	int n, k;
	cin >> n >> k;
	vector<vector<int>> g(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}

	vector<int> fa(n + 1), order, stk;
	stk.pb(1);
	fa[1] = -1;
	while (!stk.empty()) {
		auto u = stk.back();
		stk.pop_back();
		order.pb(u);
		for (auto v : g[u]) {
			if (v != fa[u]) {
				fa[v] = u;
				stk.pb(v);
			}
		}
	}

	vector<int> sz(n + 1, 1);
	for (int i = order.size() - 1; i >= 0; --i) {
		int u = order[i];
		for (auto v : g[u]) {
			if (v != fa[u]) {
				sz[u] += sz[v];
			}
		}
	}

	ll ans = n;
	for (int i = 2; i <= n; ++i) {
		int s = sz[i];
		if (s >= k) ans += n - s;
		if (n - s >= k) ans += s;
	}

	cout << ans << "\n";
}
```



# G Mukhammadali and the Smooth Array

把不改的下标视为一个子序列。因为“改”的位置可以被改成任意整数，我们只需要保证保留的下标对应的原数组值是非递减的，这样可以把改的位置填入合适的值使整个数组非递减。

改某个位置的代价是 $c_i$ 。如果我们保留若干下标 $S$ ，总改费就是总费用 $\sum c_i$ 减去保留下标的费用之和 $\sum_{i\in S}$ 。所以问题等价于：在数组 $a$ 上找一个 非递减子序列，使得保留下标对应的 $c_i$ 之和最大。

令 `dp[i]` 为以位置 `i` 结尾的、且满足非递减（按 `a`）的子序列所能获得的最大 `c` 和（即包含 `i` 的最大权值）。则

```r
dp[i] = c[i] + max{ dp[j] : j < i 且 a[j] <= a[i] }, 
（若无满足的 j 则 max 部分为 0）
```

最终取 `best = max_i dp[i]`，答案为 `total_c - best`。

```cpp
void solve() {
	int n;
	cin >> n;
	vector<ll> a(n), c(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	ll tot = 0;
	for (int i = 0; i < n; ++i) cin >> c[i], tot += c[i];

	vector<ll> dp(n);
	ll best = 0;
	for (int i = 0; i < n; i++) {
		dp[i] = c[i];
		for (int j = 0; j < i; j++) {
			if (a[j] <= a[i]) dp[i] = max(dp[i], dp[j] + c[i]);
		}
		best = max(best, dp[i]);
	}
	cout << tot - best << "\n";
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
#define rall(a) a.rbegin(),a.rend();
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef __int128 lll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef tuple<ll, ll, ll> TLLL;
typedef __gnu_pbds::tree<PLL, __gnu_pbds::null_type, less<PLL>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;

const int inf = (ll)1e9 + 7;
const ll INF = (ll)2e18 + 9;
// const ll INF = (ll)4e18;
// const ll P = 1e9 + 7;
const ll P = 998244353;
const ld PI = 3.14159265358979323;
const int mxth = 650;

template<typename T> inline void rd(T &x) {x = 0; short f = 1; char ch = getchar(); while (!isdigit(ch)) {if (ch == '-') f = -1; ch = getchar();} while (isdigit(ch)) {x = (x << 3) + (x << 1) + (ch ^ 0x30); ch = getchar();} x *= f;}
template<typename T> inline void pt(T x) {if (x < 0) putchar('-'), x = -x; if (x > 9) pt(x / 10); putchar(x % 10 | 0x30);}
template<typename T> inline void print(T a, char end = '\n') {pt(a), putchar(end);}
template<typename T> inline void print(vector<T> a) {for (auto v : a) print(v, ' '); puts("");}
template<typename T> inline void print(T a) {for (auto [u, v] : a) putchar('['), print(v, ','), puts(']'); puts("");}

inline ll ksm(ll a, ll b, ll MOD = P) {ll res = 1; a %= MOD; while (b) {if (b & 1) {res = (res * a) % MOD;} a = (a * a) % MOD; b >>= 1;} return res % MOD;}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

void init() {

}

void solve() {
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    init();

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

