// Problem: 东风谷早苗与博丽灵梦
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120564/D
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

template <class T>
T exgcd(T a, T b, T &x, T &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    T d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

i128 flr(i128 a, i128 b) {
    if (a >= 0)
        return a / b;
    return -((-a + b - 1) / b);
}
i128 cl(i128 a, i128 b) {
    if (a >= 0)
        return (a + b - 1) / b;
    return -((-a) / b);
}

ostream &operator<<(ostream &os, __int128 n) {
    if (n == 0)
        return os << 0;
    if (n < 0) {
        os << '-';
        n = -n;
    }
    string s;
    while (n > 0) {
        s += char('0' + n % 10);
        n /= 10;
    }
    reverse(s.begin(), s.end());
    return os << s;
}

void init() {
}

void solve() {
    ll x, a, s;
    cin >> x >> a >> s;
    ll u, v, g = exgcd(a, s, u, v);
    if (x % g != 0) {
        cout << "No" << endl;
        return;
    }
    i128 k = (i128)(x / g), c10 = (i128)u * k, c20 = (i128)v * k;
    i128 s1 = (i128)(s / g), s2 = (i128)(a / g);

    i128 tmin = cl(-c10, s1), tmax = flr(c20, s2);
    if (tmin > tmax) {
        cout << "No" << endl;
        return;
    }

    i128 t0 = flr(c20 - c10, s1 + s2);

    vector<i128> cand = {tmin, tmax, t0 - 1, t0, t0 + 1};
    sort(all(cand));
    cand.erase(unique(all(cand)), cand.end());

    bool ok = false;
    i128 C1 = 0, C2 = 0, mx = ((i128)1 << 120);
    for (i128 t : cand) {
        if (t < tmin || t > tmax)
            continue;
        i128 c1 = c10 + s1 * t, c2 = c20 - s2 * t;
        if (c1 < 0 || c2 < 0)
            continue;
        i128 cur = c1 > c2 ? c1 : c2;
        if (cur < mx) {
            mx = cur;
            C1 = c1;
            C2 = c2;
            ok = true;
        }
    }
    if (!ok) {
        cout << "No" << endl;
        return;
    }
    cout << "Yes" << endl;
    cout << C1 << " " << C2 << endl;
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