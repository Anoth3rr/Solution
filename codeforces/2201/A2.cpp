// Problem: A2. Lost Civilization (Hard Version)
// Contest: Codeforces - Codeforces Round 1082 (Div. 1)
// URL: https://codeforces.com/contest/2201/problem/A2
// Memory Limit: 256 MB
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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    vector<int> nxt(n + 1, n + 1);
    int lst = n + 1;
    for (int k = n; k >= 1; --k) {
        nxt[k] = lst;
        if (k > 1 && a[k] > a[k - 1] + 1) {
            lst = k;
        }
    }

    vector<int> se(n + 1, n + 1);
    stack<int> st;
    for (int k = n; k >= 1; --k) {
        while (!st.empty() && a[st.top()] > a[k]) {
            st.pop();
        }
        if (!st.empty()) {
            se[k] = st.top();
        }
        st.push(k);
    }

    vector<int> N(n + 1);
    for (int k = 1; k <= n; ++k) {
        N[k] = min(nxt[k], se[k]);
    }

    vector<ll> S(n + 2, 0);
    for (int k = 1; k <= n; ++k) {
        S[k] = 1;
    }

    ll tot = 0;
    for (int k = 1; k <= n; ++k) {
        if (N[k] <= n) {
            S[N[k]] += S[k];
        }
        tot += S[k] * (n - k + 1);
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