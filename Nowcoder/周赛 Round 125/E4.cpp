#include <bits/stdc++.h>
#define pb push_back
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
    int n, q;
    cin >> n >> q;

    vector<ll> a(n + 1), s(n + 1, 0), pre(n + 2, INF), suf(n + 2, INF);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
        pre[i] = min(pre[i - 1], a[i]);
    }

    for (int i = n; i >= 1; i--) {
        suf[i] = min(suf[i + 1], a[i]);
    }

    int L = 1, R = n;
    ll s1 = a[1], s2 = a[n];

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int i;
            cin >> i;
            L = max(L, i);

            if (L < R) {
                s1 = min(s1, pre[L]);
            } else {
                s1 = pre[n];
                R = L + 1;
            }
        } else if (op == 2) {
            int i;
            cin >> i;
            R = min(R, i);

            if (L < R) {
                s2 = min(s2, suf[R]);
            } else {
                s2 = pre[n];
                L = R - 1;
            }
        } else {
            ll ans = s1 * L + s2 * (n - R + 1) + (s[R - 1] - s[L]);
            cout << ans << endl;
        }
    }
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