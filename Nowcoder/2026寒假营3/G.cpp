// Problem: スピカの天秤
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120563/G
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
    ll Sa = 0, Sb = 0;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i)
        cin >> a[i], Sa += a[i];
    for (int i = 0; i < m; ++i)
        cin >> b[i], Sb += b[i];
    sort(all(a));
    sort(all(b));
    if (Sa == Sb) {
        cout << 1 << endl;
    } else if (Sa > Sb) {
        int cnt = 0;
        while (Sa > Sb) {
            Sa -= a.back();
            a.pob();
            cnt++;
        }
        cout << cnt << endl;
    } else {
        int cnt = 0;
        while (Sb > Sa) {
            Sb -= b.back();
            b.pob();
            cnt++;
        }
        cout << cnt << endl;
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