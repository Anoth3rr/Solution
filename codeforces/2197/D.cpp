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
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    int B = sqrt(n);
    ll ans = 0;

    for (int i = 1; i <= n; ++i) {
        if (a[i] > B) {
            for (ll k = 1;; ++k) {
                ll j = i + 1ll * a[i] * k;
                if (j > n)
                    break;
                if (a[j] == k) {
                    ans++;
                }
            }
        }
    }

    for (int j = 1; j <= n; ++j) {
        if (a[j] > B) {
            for (ll k = 1;; ++k) {
                ll i = j - 1ll * a[j] * k;
                if (i < 1)
                    break;
                if (a[i] == k) {
                    ans++;
                }
            }
        }
    }

    vector<vector<int>> pos(B + 1);
    for (int i = 1; i <= n; ++i) {
        if (a[i] <= B) {
            pos[a[i]].pb(i);
        }
    }

    for (int u = 1; u <= B; ++u) {
        if (pos[u].empty())
            continue;
        for (int v = 1; v <= B; ++v) {
            ll diff = 1ll * u * v;
            if (diff >= n)
                break;

            for (int i : pos[u]) {
                int j = i + diff;
                if (j > n)
                    break;
                if (a[j] == v) {
                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";
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