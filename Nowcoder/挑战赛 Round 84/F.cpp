// Problem: 「SFCOI-4」追忆的残响
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120679/F
// Memory Limit: 2048 MB
// Time Limit: 20000 ms
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
constexpr int N = 15000005;

int mn[N], mx[N];
ll C[N];
int S[N / 5 + 1000];
ll G[N / 25 + 1000];
struct Q {
    int n, m, i;
};

int smooth2[30];
int cnt2 = 0;
int smooth3[300];
int cnt3 = 0;

vector<int> P;

void init() {
    for (ll k = 1; k < N; k *= 2) {
        smooth2[cnt2++] = k;
    }
    // p=3
    int q[300];
    int head = 0, tail = 0;
    q[tail++] = 1;
    smooth3[cnt3++] = 1;
    while (head < tail) {
        int u = q[head++];
        if ((ll)u * 2 < N) {
        }
    }
    cnt3 = 0;
    for (ll p3 = 1; p3 < N; p3 *= 3) {
        for (ll val = p3; val < N; val *= 2) {
            smooth3[cnt3++] = val;
        }
    }
    sort(smooth3, smooth3 + cnt3);

    mn[1] = N;
    mx[1] = 1;
    C[1] = 1;

    for (int i = 2; i < N; ++i) {
        if (!mn[i]) {
            mn[i] = i;
            mx[i] = i;
            P.push_back(i);
        }
        for (int p : P) {
            if (p > mn[i] || (ll)i * p >= N) break;
            int k = i * p;
            mn[k] = p;
            mx[k] = mx[i];
        }
        C[i] = C[i - 1] + (i - i / mx[i]);
    }
}

void solve() {
    int t;
    cin >> t;
    vector<Q> qs(t);
    int max_m = 0;
    for (int i = 0; i < t; ++i) {
        cin >> qs[i].n >> qs[i].m;
        qs[i].i = i;
        if (qs[i].n > qs[i].m) swap(qs[i].n, qs[i].m);
        if (qs[i].m > max_m) max_m = qs[i].m;
    }

    sort(qs.begin(), qs.end(), [](const Q &a, const Q &b) { return a.m < b.m; });

    vector<ll> ans(t);
    for (int i = 0; i < t; ++i) {
        ans[qs[i].i] = C[qs[i].n] + (ll)qs[i].n * qs[i].m - 1;
    }

    for (int i = 1; i <= max_m / 2 + 1; ++i) S[i] = i;
    int lim_g_init = max_m / 4 + 2;
    for (int i = 1; i <= lim_g_init; ++i) G[i] = 1;

    int q_start = 0;

    for (int p : P) {
        ll p2_ll = (ll)p * p;
        if (p2_ll > max_m) break;
        int p2 = (int)p2_ll;

        while (q_start < t && qs[q_start].m < p2) {
            q_start++;
        }
        if (q_start == t) break;

        int lim_g = max_m / p2;
        for (int k = 1; k <= lim_g; ++k) {
            G[k] += (ll)p * G[k / p];
        }

        for (int i = q_start; i < t; ++i) {
            int n = qs[i].n;
            int m = qs[i].m;

            int lim = n / p;
            int bound = m / p2;
            if (lim > bound) lim = bound;

            if (lim == 0) continue;

            int X = n / p;
            int Y = m / p;
            ll cur = 0;

            for (int l = 1, r; l <= lim; l = r + 1) {
                int v1 = X / l;
                int v2 = Y / l;

                int r1 = (v1 ? X / v1 : lim);
                int r2 = (v2 ? Y / v2 : lim);
                r = (r1 < r2 ? r1 : r2);
                if (r > lim) r = lim;

                ll sum = G[r] - G[l - 1];
                if (sum) {
                    cur += sum * ((ll)S[v1] * S[v2] - 1);
                }
            }
            ans[qs[i].i] += cur * (p - 1);
        }

        int lim_s = max_m / p;
        for (int k = lim_s; k >= 1; --k) {
            S[k] -= S[k / p];
        }
    }

    for (int i = 0; i < t; ++i) {
        cout << ans[i] << "\n";
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