// Problem: 小L的字符串
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120566/J
// Memory Limit: 512 MB
// Time Limit: 8000 ms
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

typedef complex<double> cd;
const double PI = acos(-1);

void fft(vector<cd> &a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd &x : a)
            x /= n;
    }
}

void init() {
}

void solve() {
    int n;
    string s, t;
    cin >> n >> s >> t;

    ll ss = 0, st = 0;
    for (auto v : s)
        ss += v - 'a';
    for (auto v : t)
        st += v - 'a';
    ll diff = st - ss;

    string rev = s;
    reverse(all(rev));

    string tt = t + t;

    int m = 1;
    while (m < n + 2 * n)
        m <<= 1;

    vector<cd> SumFA(m, 0), Res(m, 0), P(m), fac(m), fbc(m);

    for (int c = 25; c >= 0; c--) {
        fill(all(P), cd(0, 0));

        for (int i = 0; i < n; i++) {
            if (rev[i] - 'a' == c)
                P[i].real(1);
        }
        for (int i = 0; i < 2 * n; i++) {
            if (tt[i] - 'a' == c)
                P[i].imag(1);
        }

        fft(P, 0);

        for (int i = 0; i < m; i++) {
            int j = (m - i) & (m - 1);
            cd cp = conj(P[j]);
            fac[i] = (P[i] + cp) * 0.5;
            fbc[i] = (P[i] - cp) * cd(0, -0.5);

            Res[i] += SumFA[i] * fbc[i];

            SumFA[i] += fac[i];
        }
    }

    fft(Res, 1);

    ll mn = -1;

    for (int k = 0; k < n; k++) {
        ll count = (ll)(Res[n - 1 + k].real() + 0.5);

        ll cur = k + diff + 26 * count;

        if (mn == -1 || cur < mn) {
            mn = cur;
        }
    }

    cout << mn << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    // cin >> t;
    cout << fixed << setprecision(15);
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }

    return 0;
}