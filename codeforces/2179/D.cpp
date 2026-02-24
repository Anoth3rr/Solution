// Problem: D. Blackslex and Penguin Civilization
// Contest: Codeforces - Codeforces Round 1071 (Div. 3)
// URL: https://codeforces.com/contest/2179/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// By: Anoth3r
//
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {
    uniform_int_distribution<unsigned long long> dist(l, r);
    return dist(rng);
}

vector<int> p2(32);
void init() {
    p2[0] = 1;
    for (int i = 1; i < 32; ++i)
        p2[i] = p2[i - 1] << 1;
}

void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << "1 0" << endl;
        return;
    }
    vector<bool> a(1 << n, 0);
    int base = 1 << n;
    while (base != 1) {
        a[base - 1] = 1;
        cout << base - 1 << " ";
        int cur = base - 1;
        while (cur + base < (1 << n)) {
            cur += base;
            if (!a[cur])
                cout << cur << " ";
            a[cur] = 1;
        }
        base >>= 1;
    }
    for (int i = 0; i < (1 << n); i += 2) {
        if (!a[i]) {
            cout << i << " ";
        }
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