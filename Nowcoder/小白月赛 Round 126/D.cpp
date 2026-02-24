// Problem: 小红越级（easy）
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126282/D
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

    vector<int> diff(n + 2, 0);

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;

        int l1 = a - 1, r1 = a + 1, l2 = b - 1, r2 = b + 1;

        if (r1 + 1 >= l2) {
            int L = max(1, l1);
            int R = min(n, r2);
            if (L <= R) {
                diff[L]++;
                if (R + 1 <= n + 1) {
                    diff[R + 1]--;
                }
            }
        } else {
            int L1 = max(1, l1);
            int R1 = min(n, r1);
            if (L1 <= R1) {
                diff[L1]++;
                if (R1 + 1 <= n + 1) {
                    diff[R1 + 1]--;
                }
            }

            int L2 = max(1, l2);
            int R2 = min(n, r2);
            if (L2 <= R2) {
                diff[L2]++;
                if (R2 + 1 <= n + 1) {
                    diff[R2 + 1]--;
                }
            }
        }
    }

    vector<int> cnt(n + 1);
    int cur = 0;
    for (int i = 1; i <= n; ++i) {
        cur += diff[i];
        cnt[i] = cur;
    }

    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << n - cnt[k] << " ";
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