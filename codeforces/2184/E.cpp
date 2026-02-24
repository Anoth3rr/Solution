// Problem: E. Exquisite Array
// Contest: Codeforces - Codeforces Round 1072 (Div. 3)
// URL: https://codeforces.com/contest/2184/problem/E
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
    int n;
    cin >> n;
    vector<int> a(n), diff(n - 1);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n - 1; ++i) {
        diff[i] = abs(a[i] - a[i + 1]);
    }

    vector<int> L(n - 1), R(n - 1);
    vector<int> stk;

    for (int i = 0; i < n - 1; ++i) {
        while (stk.size() && diff[stk.back()] >= diff[i]) {
            stk.pob();
        }
        if (stk.empty()) {
            L[i] = 0;
        } else {
            L[i] = stk.back() + 1;
        }
        stk.pb(i);
    }

    while (!stk.empty()) stk.pob();

    for (int i = n - 2; i >= 0; --i) {
        while (stk.size() && diff[stk.back()] > diff[i]) {
            stk.pob();
        }
        if (stk.empty()) {
            R[i] = n - 2;
        } else {
            R[i] = stk.back() - 1;
        }
        stk.pb(i);
    }

    vector<ll> cnt(n + 1, 0);
    for (int i = 0; i < n - 1; ++i) {
        ll c = 1ll * (i - L[i] + 1) * (R[i] - i + 1);
        cnt[diff[i]] += c;
    }

    vector<ll> ans(n);
    ll cur = 0;

    for (int i = n - 1; i >= 1; --i) {
        if (i < cnt.size()) {
            cur += cnt[i];
        }
        ans[i] = cur;
    }

    for (int i = 1; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
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