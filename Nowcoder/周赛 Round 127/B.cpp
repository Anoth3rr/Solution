// Problem: Sudoku
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126949/B
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
using ull = unsigned long long;
using i128 = __int128;
using PII = pair<int, int>;
using PLL = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using TLLL = tuple<ll, ll, ll>;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ld eps = 1e-10;

void init() {}

void solve() {
    int n = 4;
    unordered_set<string> st;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0, x; j < n; ++j) {
            string s1 = "r" + to_string(i) + "#" + to_string(a[i][j]);
            string s2 = "c" + to_string(j) + "#" + to_string(a[i][j]);
            string s3 = "b" + to_string(i / 2 * 2 + j / 2) + "#" + to_string(a[i][j]);
            if (st.count(s1) || st.count(s2) || st.count(s3)) {
                cout << "NO" << endl;
                return;
            }

            st.insert(s1);
            st.insert(s2);
            st.insert(s3);
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
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}