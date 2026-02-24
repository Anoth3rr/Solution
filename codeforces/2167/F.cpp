#include<bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<std::vector<int>> g(n + 1);
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	std::vector<int> fa(n + 1), order, stk;
	stk.push_back(1);
	fa[1] = -1;
	while (!stk.empty()) {
		auto u = stk.back();
		stk.pop_back();
		order.push_back(u);
		for (auto v : g[u]) {
			if (v != fa[u]) {
				fa[v] = u;
				stk.push_back(v);
			}
		}
	}

	std::vector<int> sz(n + 1, 1);
	for (int i = order.size() - 1; i >= 0; --i) {
		int u = order[i];
		for (auto v : g[u]) {
			if (v != fa[u]) {
				sz[u] += sz[v];
			}
		}
	}

	i64 ans = n;
	for (int i = 2; i <= n; ++i) {
		int s = sz[i];
		if (s >= k) ans += n - s;
		if (n - s >= k) ans += s;
	}

	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t = 1;
	std::cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}