// Problem: 差异
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/128672/F
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
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    vector<int> c(m);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        for (int j = 0; j < m; ++j) {
            c[j] += s[i][j] == '0';
        }
    }
    for (int i = 0; i < n; ++i) {
        int diff = 0;
        for (int j = 0; j < m; ++j) {
            diff += s[i][j] == '0' ? n - c[j] : c[j];
        }
        int cur = 0, best = 0;
        for (int j = 0; j < m; ++j) {
            int d;
            if (s[i][j] == '1')
                d = 2ll * (n - c[j]) - n - 1;
            else
                d = n - 2 * (n - c[j]) - 1;
            cur = min(0, cur + d);
            if (cur < best)
                best = cur;
        }
        cout << diff + best << endl;
    }
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