#include<bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

void solve() {
	int tar;
	bool f = true;
	std::cin >> tar;
	for (int i = 0, x; i < 3; ++i) {
		std::cin >> x;
		if (x != tar) f = false;
	}
	if (f) std::cout << "YES" << "\n";
	else std::cout << "NO" << "\n";
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