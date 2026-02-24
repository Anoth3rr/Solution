//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(),a.rend()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef __int128 lll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef tuple<ll, ll, ll> TLLL;
typedef __gnu_pbds::tree<PLL, __gnu_pbds::null_type, less<PLL>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;
// typedef __gnu_pbds::tree<ll, __gnu_pbds::null_type, less<ll>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ld PI = acos(-1.0);
constexpr ld eps = 1e-10;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

ll cal(ll tot, ll num) {
    if (num <= 0) {
        return 0;
    }
    return tot - (num - 1);
}

void init() {

}

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<ll> pre(n + 1), suf(n + 1);
    for (int i = 0; i < n; ++i) {
        pre[i + 1] = pre[i] + a[i];
    }
    for (int i = n - 1; i >= 0; --i) {
        suf[i] = suf[i + 1] + a[i];
    }

    vector<int> nxt(n + 1, n);
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] > 1) {
            nxt[i] = i;
        } else {
            if (i + 1 <= n) {
                nxt[i] = nxt[i + 1];
            }
        }
    }

    ll ans = -1;
    for (int i = 0; i < n; ++i) {
        ll cur = a[i];

        if (i > 0) {
            cur += pre[i] - (i - 1);
        }

        if (i < n - 1) {
            ll ini = i + 1;

            if (a[i + 1] > ini) {
                int idx = i + 1;
                cur += suf[idx] - ini - (n - idx - 1);
            } else {
                int idx = n;
                if (i + 2 < n) {
                    idx = nxt[i + 2];
                }

                if (idx < n) {
                    cur += suf[idx] - 1 - (n - idx - 1);
                }
            }
        }

        if (ans == -1 || cur < ans) {
            ans = cur;
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
    while (t--) {
        solve();
    }
    return 0;
}