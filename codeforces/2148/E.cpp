//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define _0x0_ cin
#define _0w0_ cout
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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), cnt(n + 1, 0);
    for (int i = 0; i < n; ++i) cin >> a[i], cnt[a[i]]++;
    bool ok = true;
    vector<int> cap(n + 1, 0);
    for (int v = 1; v <= n; ++v) {
        if (cnt[v] % k != 0) {
            ok = false;
            break;
        }
        cap[v] = cnt[v] / k;
    }
    if (!ok) {
        cout << 0 << "\n";
        return;
    }
    vector<int> freq(n + 1, 0);
    ll ans = 0;
    int l = 0;
    for (int r = 0; r < n; ++r) {
        freq[a[r]]++;
        while (freq[a[r]] > cap[a[r]]) {
            freq[a[l]]--;
            ++l;
        }
        ans += (r - l + 1);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    init();

    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    return 0;
}