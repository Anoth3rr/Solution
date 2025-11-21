//Anoth3r
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef __int128 i128;
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

void init() {

}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    bool f = true;
    for (int i = 1; i < n; ++i) {
        if (a[i] <= a[i - 1]) {
            f = false;
            break;
        }
    }
    if (f) {
        cout << 0 << "\n";
        return;
    }

    auto check = [&](int d) -> bool {
        ll val = a[0], del = 0, cnt = 0;
        for (int i = 1; i < n; ++i) {
            if (a[i] > val) {
                ll k = 0;
                if (k > del) {
                    cnt += (k - del);
                    if (cnt > m) return false;
                }
                del = k;
                val = a[i];
            } else {
                ll need = (val - a[i]) / d + 1;
                if (need > m) return false;
                if (need > del) {
                    cnt += (need - del);
                    if (cnt > m) return false;
                }
                del = need;
                val = a[i] + need * d;
            }
        }
        return cnt <= m;
    };

    ll l = 0, r = inf, ans = r;
    while (l <= r) {
        ll mid = l + r >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if (ans == inf) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
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