// Problem: 模糊匹配
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/127255/A
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// By: Anoth3r

#include <bits/stdc++.h>
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define endl "\n"
using namespace std;

using ll = long long;
using ld = long double;
using ui = unsigned;
using ull = unsigned long long;
using i128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<ll, ll, ll>;

void init() {
}

void solve() {
    int n;
    string s1, s2;
    cin >> n >> s1 >> s2;
    auto cmp = [&](char a, char b) -> bool {
        vector<string> f = {"0O", "1Il"};
        for (auto s : f) {
            for (auto c1 : s)
                for (auto c2 : s)
                    if (a == c1 && b == c2)
                        return true;
        }
        return a == b;
    };
    for (int i = 0; i < n; ++i) {
        if (!cmp(s1[i], s2[i])) {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    cin >> t;
    cout << fixed << setprecision(15);
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}