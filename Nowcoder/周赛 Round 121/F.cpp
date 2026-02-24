//Another
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
constexpr int maxn = 100;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

vector<int> primes, spf(maxn + 1);
int P;

void init() {
    for (int i = 2; i <= maxn; ++i) {
        if (!spf[i]) primes.push_back(i), spf[i] = i;
        for (int j = 0; primes[j]*i <= maxn; ++j) {
            int m = primes[j] * i;
            spf[m] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
    P = primes.size();
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> mask(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        int x = a[i], m = 0;
        for (int j = 0; j < P; ++j) {
            int cnt = 0;
            while (x % primes[j] == 0) {
                x /= primes[j];
                cnt ^= 1;
            }
            if (cnt) m |= (1 << j);
        }
        mask[i] = m;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;

        if (len > P) {
            cout << "Yes" << "\n";
            continue;
        }

        vector<int> masks;
        bool z = false;
        for (int i = l; i <= r; ++i) {
            if (mask[i] == 0) {
                z = true;
                break;
            }
            masks.pb(mask[i]);
        }
        if (z) {
            cout << "Yes" << "\n";
            continue;
        }

        sort(all(masks));
        bool f = false;
        for (int i = 1; i < masks.size(); ++i) {
            if (masks[i] == masks[i - 1]) {
                f = true;
                break;
            }
        }
        if (f) {
            cout << "Yes" << "\n";
            continue;
        }

        int rank = 0;
        vector<int> basis(P, 0);
        for (int m : masks) {
            int cur = m;
            for (int b = P - 1; b >= 0; --b) {
                if ((cur >> b) & 1) {
                    if (!basis[b]) {
                        basis[b] = cur;
                        ++rank;
                        break;
                    } else {
                        cur ^= basis[b];
                    }
                }
            }
        }

        if (rank < len) cout << "Yes" << "\n";
        else cout << "No" << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}