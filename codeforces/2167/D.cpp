#include<bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

constexpr int maxn = 5e5;

std::vector<int> spf(maxn + 10), primes;

void init() {
	for (int i = 2; i <= maxn; ++i) {
		if (!spf[i]) spf[i] = i, primes.push_back(i);
		for (int j = 0; primes[j]*i <= maxn; ++j) {
			int m = primes[j] * i;
			spf[m] = primes[j];
			if (i % primes[j] == 0) break;
		}
	}
}

void solve() {
	int n;
	std::cin >> n;
	std::vector<i64> a(n);
	for (int i = 0; i < n; ++i) std::cin >> a[i];
	i64 ans = -1;
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
	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	init();

	int t = 1;
	std::cin >> t;

	while (t--) {
		solve();
	}

	return 0;
}