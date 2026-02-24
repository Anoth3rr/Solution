#include<bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

void solve() {
	int n;
	std::string s;
	std::vector<int> dic(26);

	std::cin >> n >> s;
	for (auto v : s) dic[v - 'a']++;
	std::cin >> s;
	for (auto v : s) dic[v - 'a']--;
	for (auto v : dic) {
		if (v) {
			std::cout << "NO" << "\n";
			return;
		}
	}
	std::cout << "YES" << "\n";
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