#include<bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	bool f, ok = true;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		if (i == 0) f = a[i] & 1;
		if ((a[i] & 1) != f) ok = false;
	}
	if (ok) {
		for (int i = 0; i < n; ++i) std::cout << a[i] << " ";
		std::cout << "\n";
		return;
	}

	std::sort(a.begin(), a.end());

	for (int i = 0; i < n; ++i) {
		std::cout << a[i] << " ";
	}

	std::cout << "\n";
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