//SakurabaEma
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
    string a, b;
    cin >> a >> b;
    int n = a.size();
    if (b.size() != n) {
        cout << -1 << "\n";
        return;
    }

    int ca[2] = {0, 0}, cb[2] = {0, 0};
    for (char c : a) ca[c - '0']++;
    for (char c : b) cb[c - '0']++;
    if (ca[0] != cb[0] || ca[1] != cb[1]) {
        cout << -1 << "\n";
        return;
    }

    string A = a + a;
    int m = n;

    vector<int> pi(m, 0);
    for (int i = 1; i < m; ++i) {
        int j = pi[i - 1];
        while (j > 0 && b[i] != b[j]) j = pi[j - 1];
        if (b[i] == b[j]) ++j;
        pi[i] = j;
    }

    int j = 0;
    int ans = -1;

    for (int i = 0; i < A.size(); ++i) {
        while (j > 0 && A[i] != b[j]) j = pi[j - 1];
        if (A[i] == b[j]) ++j;
        if (j == m) {
            int st = i - m + 1;
            if (st < n) {
                ans = st;
                break;
            }
            j = pi[j - 1];
        }
    }

    if (ans == -1) cout << -1 << "\n";
    else cout << ans << "\n";

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
