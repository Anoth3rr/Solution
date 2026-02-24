// Problem: 小L的线段树
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120566/C
// Memory Limit: 512 MB
// Time Limit: 4000 ms
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
    cin >> n;
    int N = 4 * n + 5;
    vector<bool> flg(N);
    vector<int> val(N);
    function<void(int, int, int)> build = [&](int x, int l, int r) {
        val[x] = 1;
        flg[x] = 0;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(2 * x, l, mid);
        build(2 * x + 1, mid + 1, r);
    };

    build(1, 1, n);

    function<void(int, int, int, int, int)> update = [&](int x, int l, int r, int ql, int qr) {
        if (l == ql && r == qr) {
            if (!flg[x]) {
                flg[x] = true;
                val[x] = val[2 * x] + val[2 * x + 1];
            }
            return;
        }

        int mid = (l + r) >> 1;
        if (qr <= mid)
            update(2 * x, l, mid, ql, qr);
        else
            update(2 * x + 1, mid + 1, r, ql, qr);

        if (flg[x]) {
            val[x] = val[2 * x] + val[2 * x + 1];
        }
    };

    function<int(int, int, int, int, int)> ask = [&](int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return val[x];
        }

        int res = flg[x] ? 0 : 1;
        int mid = (l + r) >> 1;
        if (ql <= mid)
            res += ask(2 * x, l, mid, ql, qr);
        if (qr > mid)
            res += ask(2 * x + 1, mid + 1, r, ql, qr);
        return res;
    };

    for (int i = 0; i < n; ++i) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            update(1, 1, n, l, r);
        } else {
            cout << ask(1, 1, n, l, r) << "\n";
        }
    }
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