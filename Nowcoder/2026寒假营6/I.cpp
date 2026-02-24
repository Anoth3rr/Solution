// Problem: 小L的构造2
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120566/I
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
    cin >> n;
    if (n == 4) {
        cout << "3 4 2 1" << endl;
        return;
    }
    vector<int> b, g, s6, s3;
    for (int i = 1; i <= n; ++i) {
        if (i % 6 == 0)
            s6.eb(i);
        else if (i % 2 == 0)
            b.eb(i);
        else if (i % 3 == 0)
            s3.eb(i);
        else
            g.eb(i);
    }
    if (s6.empty())
        g.insert(all(g), s3.end());
    else {
        b.insert(b.end(), all(s6));
        b.insert(b.end(), all(s3));
    }
    if (g.size() > b.size() / 2 + 1) {
        cout << -1 << endl;
        return;
    }
    int j = 0;
    for (auto x : g) {
        cout << x << " ";
        for (int _ = 1; _ <= 2; ++_)
            if (j < b.size())
                cout << b[j++] << " ";
    }
    while (j < b.size())
        cout << b[j++] << " ";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    cout << fixed << setprecision(15);
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}