// Problem: 智乃的矩阵
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120565/H
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
    ll tot = 0, sum = 0, cnt = 0;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> a[i][j], tot += a[i][j], sum += (!(i + j & 1)) * a[i][j], cnt += !(i + j & 1);
    if (n == 1) {
        cout << "Yes" << endl;
        return;
    }
    if (tot % (n * n) != 0) {
        cout << "No" << endl;
        return;
    }
    ll T = tot / (n * n);
    if (sum != cnt * T) {
        cout << "No" << endl;
        return;
    }
    vector<vector<int>> b(n + 2, vector<int>(n + 2));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            b[i][j] = ((a[i][j] - T) % 2 + 2) % 2;
        }
    }
    vector<vector<int>> x(n + 2, vector<int>(n + 2));
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            x[i][j] = b[i][j] ^ x[i - 1][j] ^ x[i][j - 1] ^ x[i - 1][j - 1];
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int cur = 0;
            if (i < n && j < n)
                cur ^= x[i][j];
            if (i > 1 && j < n)
                cur ^= x[i - 1][j];
            if (i < n && j > 1)
                cur ^= x[i][j - 1];
            if (i > 1 && j > 1)
                cur ^= x[i - 1][j - 1];

            if (cur != b[i][j]) {
                cout << "No" << endl;
                return;
            }
        }
    }

    cout << "Yes" << endl;
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