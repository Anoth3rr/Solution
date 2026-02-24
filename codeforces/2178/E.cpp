// Problem: E. Flatten or Concatenate
// Contest: Codeforces - Good Bye 2025
// URL: https://codeforces.com/contest/2178/problem/E
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// By: Anoth3r

#include <bits/stdc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
// #define endl "\n"
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
constexpr ld eps = 1e-9;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct itv {
    int l, r;
    ll sum;
    double avg;
    int str;
    bool operator<(const itv &o) const { return avg < o.avg; }
};

int L;

ll ask(int l, int r) {
    if (L <= 0)
        return -1;
    cout << "? " << l << ' ' << r << endl;
    L--;
    ll res;
    cin >> res;
    if (res == -1)
        exit(0);
    return res;
}

void init() {}

void solve() {
    int n;
    cin >> n;

    L = 300;

    ll tot = ask(1, n);

    if (n == 1) {
        cout << "! " << tot << endl;
        return;
    }

    ll ans = 0;

    priority_queue<itv> pq;
    pq.push({1, n, tot, (double)tot / n, 0});

    while (!pq.empty() && L > 0) {
        itv cur = pq.top();
        pq.pop();

        if (ans > 0 && cur.sum < 2 * ans) {
            continue;
        }

        if (cur.l == cur.r) {
            if (cur.sum > ans)
                ans = cur.sum;
            continue;
        }

        int len = cur.r - cur.l + 1;

        if (cur.str >= 2 && len >= 4 && cur.sum % len == 0) {
            int idx = cur.l + rng() % len;
            ll val = ask(idx, idx);

            if (val == -1)
                break;

            if (val > ans)
                ans = val;

            if (val == (cur.sum / len)) {
                continue;
            }

            if (ans > 0 && cur.sum < 2 * ans) {
                continue;
            }
        }

        int mid = (cur.l + cur.r) / 2;
        ll sl = ask(cur.l, mid);
        if (sl == -1)
            break;

        ll sr = cur.sum - sl;

        int lenl = mid - cur.l + 1;
        int lenr = cur.r - mid;

        double al = (double)sl / lenl;
        double ar = (double)sr / lenr;

        bool eql = ((i128)sl * len == (i128)cur.sum * lenl);
        bool eqr = ((i128)sr * len == (i128)cur.sum * lenr);

        int stl = eql ? cur.str + 1 : 0;
        int str = eqr ? cur.str + 1 : 0;

        if (ans == 0 || sl >= 2 * ans) {
            pq.push({cur.l, mid, sl, al, stl});
        }
        if (ans == 0 || sr >= 2 * ans) {
            pq.push({mid + 1, cur.r, sr, ar, str});
        }
    }

    cout << "! " << ans << endl;
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