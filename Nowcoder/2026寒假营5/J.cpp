// Problem: 智乃的幻方
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120565/J
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
    vector<vector<int>> a(3, vector<int>(3));
    unordered_set<int> st;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> a[i][j];
            st.insert(a[i][j]);
        }
    }
    if (st.size() != 9) {
        cout << "No" << endl;
        return;
    }
    int S = a[0][0] + a[0][1] + a[0][2];
    for (int i = 0; i < 3; ++i) {
        int s = 0;
        for (int j = 0; j < 3; ++j) {
            s += a[i][j];
        }
        if (s != S) {
            cout << "No" << endl;
            return;
        }
    }
    for (int i = 0; i < 3; ++i) {
        int s = 0;
        for (int j = 0; j < 3; ++j) {
            s += a[j][i];
        }
        if (s != S) {
            cout << "No" << endl;
            return;
        }
    }
    if (a[0][0] + a[1][1] + a[2][2] != S) {
        cout << "No" << endl;
        return;
    }
    if (a[2][0] + a[1][1] + a[0][2] != S) {
        cout << "No" << endl;
        return;
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