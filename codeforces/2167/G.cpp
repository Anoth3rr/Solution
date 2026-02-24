#include<bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

void solve() {
	int n;
	std::cin >> n;
	std::vector<i64> a(n), c(n);
	for (int i = 0; i < n; ++i) std::cin >> a[i];
	i64 tot = 0;
	for (int i = 0; i < n; ++i) std::cin >> c[i], tot += c[i];

	std::vector<i64> dp(n);
	i64 best = 0;
	for (int i = 0; i < n; i++) {
		dp[i] = c[i];
		for (int j = 0; j < i; j++) {
			if (a[j] <= a[i]) dp[i] = std::max(dp[i], dp[j] + c[i]);
		}
		best = std::max(best, dp[i]);
	}
	std::cout << tot - best << "\n";
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