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

void solve() {
    int n;
    cin >> n;
    unordered_map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    ll tot2 = 0, tot4 = 0;
    for (auto [u, v] : cnt) tot2 += v >= 2, tot4 += v >= 4;

    auto update(int x, int d) {
        if (cnt[x] >= 2) tot2--;
        if (cnt[x] >= 4) tot4--;

        cnt[x] += d;

        if (cnt[x] >= 2) tot2++;
        if (cnt[x] >= 4) tot4++;
    };

    ll ans = 0;
    for (auto [u, v] : cnt) {
        if (v >= 3 && cnt[u + 1] >= 3) {
            update(i, -3);
            update(i + 1, -3);

            if (tot2 >= 2) {
                ans = (ans + tot2 * (tot2 - 1) / 2) % MOD;
            }

            if (tot4 > 0) {
                ans = (ans + tot4) % MOD;
            }

            update(i, 3);
            update(i + 1, 3);
        }
    }
    cout << ans % MOD << endl;
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