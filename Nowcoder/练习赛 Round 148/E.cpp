// Problem: 小R的min
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/119900/E
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
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i], b[i] = a[i];
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    vector<int> rk(n);
    for (int i = 0; i < n; ++i) {
        rk[i] = lower_bound(all(b), a[i]) - b.begin();
    }
    vector<int> L(n), R(n);
    for (int i = 0; i < n; ++i) {
        int j = i - 1;
        while (j >= 0 && a[j] >= a[i])
            j--;
        L[i] = j;

        j = i + 1;
        while (j < n && a[j] > a[i])
            j++;
        R[i] = j;
    }
    int k = b.size();
    while (m--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int len = r - l + 1;
        ll tar = 1ll * (len * (len + 1) / 2 + 1) / 2;

        vector<int> cnt(k);

        for (int i = l; i <= r; ++i) {
            ll num = 1ll * (i - max(l, L[i] + 1) + 1) * (min(r, R[i] - 1) - i + 1);

            cnt[rk[i]] += num;
        }

        ll cur = 0;
        int ans = b.back();
        for (int i = 0; i < k; ++i) {
            cur += cnt[i];
            if (cur >= tar) {
                ans = b[i];
                break;
            }
        }
        cout << ans << endl;
    }
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