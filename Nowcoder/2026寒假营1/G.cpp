// Problem: Digital Folding
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120561/G
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

vector<ll> P(20);

void init() {
    P[0] = 1;
    for (int i = 1; i < 20; ++i)
        P[i] = P[i - 1] * 10;
}

void solve() {
    ll l, r;
    cin >> l >> r;
    ll ans = 0;

    auto rev = [&](ll x) {
        string s = to_string(x);
        reverse(all(s));
        return stoll(s);
    };
    auto siz = [&](ll x) {
        return to_string(x).size();
    };

    for (int t = 0; t < 19 && P[t] <= r; ++t) {
        ll p = P[t];
        ll A = (l + p - 1) / p, B = r / p;
        if (B <= 0)
            continue;
        if (A <= 0)
            A = 1;
        if (A > B)
            continue;

        unordered_set<ll> st;

        auto add = [&](ll x) {
            if (x < A || x > B)
                return;
            if (x % 10 == 0) {
                if (x - 1 >= A)
                    st.insert(x - 1);
                if (x + 1 <= B)
                    st.insert(x + 1);
            } else
                st.insert(x);
        };

        add(A);
        add(B);

        int la = siz(A), lb = siz(B);
        for (int len = la; len <= lb; ++len) {
            for (int k = 1; k <= len; ++k) {
                ll n1 = A - P[k] + 1, n2 = B - P[k] + 1;
                if (n2 < 0)
                    continue;
                ll mx = n2 / P[k], mn = (n1 <= 0) ? 0 : ((n1 + P[k] - 1) / P[k]);
                if (mx < mn)
                    continue;
                ll b = mx * P[k] + P[k] - 1;
                if (b >= A && b <= B && b % 10 != 0)
                    st.insert(b);
            }
        }

        for (auto b : st) {
            ll rv = rev(b);
            if (rv > ans)
                ans = rv;
        }
    }
    cout << ans << endl;
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