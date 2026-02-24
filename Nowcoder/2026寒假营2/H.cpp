// Problem: 权值计算
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120562/H
// Memory Limit: 2048 MB
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
    map<int, int> pos;
    ll tot = 0;

    auto S = [&](ll x) {
        return x * (x + 1) / 2;
    };

    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        tot += (i - pos[x]) * S(n - i + 1);
        pos[x] = i;
    }

    cout << tot << endl;
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