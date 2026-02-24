// Problem: 「SFCOI-4」剑客花木兰
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120679/A
// Memory maxn: 1024 MB
// Time maxn: 2000 ms
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
constexpr int maxn = 2e6;

template <class T> T exgcd(T a, T b, T &x, T &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    T d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll inv(ll a, ll m) {
    ll x, y;
    exgcd(a, m, x, y);
    return (x % m + m) % m;
}

void init() {}

void solve() {
    ll n, a, b;
    cin >> n >> a >> b;

    vector<int> dp(maxn, -1);
    dp[0] = 0;

    for (int i = 0; i < maxn; ++i) {
        if (dp[i] == -1) {
            continue;
        }

        if (i + a < maxn) {
            if (dp[i] > dp[i + a]) {
                dp[i + a] = dp[i];
            }
        }

        if (i + b < maxn) {
            if (dp[i] + 1 > dp[i + b]) {
                dp[i + b] = dp[i] + 1;
            }
        }
    }

    ll g = __gcd(a, b);
    ll a2 = a / g, b2 = b / g;
    ll ia = inv(a2, b2);

    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;

        if (x < 1500000) {
            int S = -1;
            for (int k = x; k < maxn; ++k) {
                if (dp[k] != -1) {
                    S = k;
                    break;
                }
            }

            cout << (S - dp[S] * b) / a << " " << dp[S] << endl;
        } else {
            ll S = (x % g == 0) ? x : (x + g - x % g);

            ll kA = (((S / g) % b2) * ia) % b2;
            ll kB = (S - kA * a) / b;

            cout << kA << " " << kB << endl;
        }
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