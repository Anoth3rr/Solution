// Problem: 爱音的01串构造
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120564/F
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
    int a, b;
    cin >> a >> b;
    if (a == 0) {
        cout << string(b, '1') << endl;
        return;
    }
    if (b == 0) {
        cout << string(a, '0') << endl;
        return;
    }
    int r0 = min(a, b + 1), r1 = min(b, a + 1);

    vector<int> A(r0, a / r0);
    for (int i = 0; i < a % r0; ++i)
        A[i]++;
    vector<int> B(r1, b / r1);
    for (int i = 0; i < b % r1; ++i)
        B[i]++;

    string ans = "";
    bool f = (r1 >= r0);
    int i1 = 0, i0 = 0;
    while (i1 < r1 || i0 < r0) {
        if (f) {
            if (i1 < r1) {
                ans.append(B[i1], '1');
                ++i1;
            }
            if (i0 < r0) {
                ans.append(A[i0], '0');
                ++i0;
            }
        } else {
            if (i0 < r0) {
                ans.append(A[i0], '0');
                ++i0;
            }
            if (i1 < r1) {
                ans.append(B[i1], '1');
                ++i1;
            }
        }
    }
    cout << ans << endl;
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