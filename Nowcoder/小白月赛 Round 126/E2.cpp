//Another
#include<bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

void init() {

}

#include<bits/extc++.h>
using namespace __gnu_pbds;
using Tree = tree<PII, null_type, less<PII>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n, q;
    cin >> n >> q;

    Tree L, R;
    int id = 0;

    auto insert = [&](int l, int r) {
        L.insert({l, ++id});
        R.insert({r, ++id});
    };

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;

        int l1 = a - 1, r1 = a + 1;
        int l2 = b - 1, r2 = b + 1;

        if (r1 + 1 >= l2) {
            insert(min(l1, l2), max(r1, r2));
        } else {
            insert(l1, r1);
            insert(l2, r2);
        }
    }

    for (int i = 0; i < q; ++i) {
        int k;
        cin >> k;
        cout << n - L.order_of_key({k, inf}) + R.order_of_key({k, -inf}) << " ";
    }
    cout << "\n";
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