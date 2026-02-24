// Problem: 躯树の墓守
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120563/E
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

void init() {
}

void solve() {
    int n;
    ll m, k;
    cin >> n >> m >> k;

    if (n == 1) {
        cout << "NO" << endl;
        return;
    }

    ll flr = 1ll * n * (n - 1) / 2;
    if (k < flr) {
        cout << "NO" << endl;
        return;
    }

    vector<ll> lim(n);
    for (int i = 1; i < n; ++i) {
        lim[i] = min(1ll * i * (i - 1) / 2 + 1, 1ll * m - (n - i - 1));
    }

    vector<ll> T(n);
    T[n - 1] = lim[n - 1];
    for (int i = n - 2; i >= 1; --i) {
        T[i] = min(lim[i], T[i + 1] - 1);
        if (T[i] < i) {
            cout << "NO" << endl;
            return;
        }
    }

    ll cl = 0;
    for (int i = 1; i < n; ++i)
        cl += T[i];
    if (k > cl) {
        cout << "NO" << endl;
        return;
    }

    vector<ll> t(n);
    for (int i = 1; i < n; ++i)
        t[i] = i;

    ll cur = flr, rem = k - cur;
    for (int i = n - 1; i >= 1; --i) {
        if (rem == 0)
            break;
        ll u = T[i];
        if (i < n - 1)
            u = min(u, t[i + 1] - 1);

        ll add = min(rem, u - t[i]);
        t[i] += add;
        rem -= add;
    }

    cout << "YES" << endl;
    vector<bool> flg(m + 2);
    for (int i = 1; i < n; ++i) {
        cout << i << " " << i + 1 << " " << t[i] << endl;
        if (t[i] <= m)
            flg[t[i]] = 1;
    }

    vector<int> nxt(n + 1, 1);
    queue<int> q;
    int ptr = 1;

    for (ll w = 1; w <= m; ++w) {
        if (w <= m && flg[w])
            continue;

        while (ptr < n && t[ptr] < w) {
            q.push(ptr + 1);
            ptr++;
        }

        while (q.size()) {
            int u = q.front();
            if (nxt[u] < u - 1) {
                cout << nxt[u] << " " << u << " " << w << endl;
                nxt[u]++;
                break;
            } else {
                q.pop();
            }
        }
    }
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