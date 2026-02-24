#include<bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

void solve() {
	i64 n, k, x;
	std::cin >> n >> k >> x;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) std::cin >> a[i];
	std::sort(a.begin(), a.end());

	auto check = [&](i64 m)->bool {
		if (m == 0) return true;
		i64 r = m - 1;
		std::vector<std::pair<i64, i64>> segs;
		for (int i = 0; i < n; ++i) {
			i64 L = a[i] - r;
			i64 R = a[i] + r;
			if (R < 0 || L > x) continue;
			L = std::max(L, 0ll);
			R = std::min(R, x);
			segs.emplace_back(L, R);
		}
		if (segs.empty()) {
			return x + 1 >= k;
		}
		sort(segs.begin(), segs.end());
		i64 tot = 0;
		i64 curL = segs[0].first, curR = segs[0].second;
		for (int i = 1; i < segs.size(); ++i) {
			if (segs[i].first <= curR + 1) {
				curR = std::max(curR, segs[i].second);
			} else {
				tot += (curR - curL + 1);
				curL = segs[i].first;
				curR = segs[i].second;
			}
		}
		tot += (curR - curL + 1);
		return x + 1 - tot >= (i64)k;
	};

	i64 lo = 0, hi = x + 1;
	while (lo < hi - 1) {
		i64 mid = lo + (hi - lo) / 2;
		if (check(mid)) lo = mid;
		else hi = mid;
	}
	i64 best = lo;

	std::vector<i64> ans;
	if (best == 0) {
		for (int i = 0; i < k; ++i) ans.push_back(i);
	} else {
		i64 r = best - 1;
		std::vector<std::pair<i64, i64>> segs;
		for (int i = 0; i < n; ++i) {
			i64 L = a[i] - r;
			i64 R = a[i] + r;
			if (R < 0 || L > x) continue;
			L = std::max(L, 0LL);
			R = std::min(R, x);
			segs.emplace_back(L, R);
		}
		if (segs.empty()) {
			for (i64 p = 0; ans.size() < k && p <= x; ++p) ans.push_back(p);
		} else {
			sort(segs.begin(), segs.end());
			std::vector<std::pair<i64, i64>> merged;
			i64 curL = segs[0].first, curR = segs[0].second;
			for (int i = 1; i < segs.size(); ++i) {
				if (segs[i].first <= curR + 1) curR = std::max(curR, segs[i].second);
				else {
					merged.emplace_back(curL, curR);
					curL = segs[i].first;
					curR = segs[i].second;
				}
			}
			merged.emplace_back(curL, curR);

			i64 cur = 0;
			for (auto &pr : merged) {
				i64 Lf = pr.first, Rf = pr.second;
				if (cur <= Lf - 1) {
					i64 from = cur, to = Lf - 1;
					for (i64 p = from; p <= to && ans.size() < k; ++p) ans.push_back(p);
				}
				cur = Rf + 1;
				if (ans.size() >= k) break;
			}
			for (i64 p = cur; p <= x && ans.size() < k; ++p) ans.push_back(p);
		}
	}

	while (ans.size() < k) {
		i64 p = 0;
		std::unordered_set<i64> used(ans.begin(), ans.end());
		while (ans.size() < k && p <= x) {
			if (!used.count(p)) {
				ans.push_back(p);
				used.insert(p);
			}
			++p;
		}
	}

	for (int i = 0; i < k; ++i) {
		std::cout << ans[i] << " ";
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