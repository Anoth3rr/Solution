// Problem: 小红越级（hard）
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126282/G
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// By: Anoth3r

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

    vector<int> diff(n + 10, 0);

    ll cur = 0;

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;

        cur += (a - 1);

        if (b - a <= 2) {
            diff[a] += 1;
            if (b + 2 <= n + 5) {
                diff[b + 2] += 1;
            }
        } else {
            diff[a] += 1;
            if (a + 2 <= n + 5) {
                diff[a + 2] += 1;
            }

            int sum = a + b;
            int m = sum / 2;
            if (sum % 2 == 0) {
                if (m + 1 <= n + 5) {
                    diff[m + 1] -= 2;
                }
            } else {
                if (m + 1 <= n + 5) {
                    diff[m + 1] -= 1;
                }

                if (m + 2 <= n + 5) {
                    diff[m + 2] -= 1;
                }
            }

            if (b <= n + 5) {
                diff[b] += 1;
            }

            if (b + 2 <= n + 5) {
                diff[b + 2] += 1;
            }
        }
    }

    vector<ll> ans(n + 1);

    ll S = -n;

    for (int k = 1; k <= n; ++k) {
        S += diff[k];
        cur += S;
        ans[k] = cur;
    }

    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << ans[k] << " ";
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