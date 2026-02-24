// Problem: D2. Little String (Hard Version)
// Contest: Codeforces - Codeforces Round 1075 (Div. 2)
// URL: https://codeforces.com/contest/2189/problem/D2
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// By: Entelechia

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

constexpr ld INF = 1e300;
constexpr ll MOD = 1000000007;
constexpr ld eps = 1e-12;

void init() {
}

void solve() {
    int n;
    ll c;
    string s;
    cin >> n >> c >> s;
    if (s[0] == '0' || s[n - 1] == '0') {
        cout << "-1" << endl;
        return;
    }
    ll x = c;
    vector<ll> pr;
    vector<int> need;
    for (ll p = 2; p * p <= x; p += (p == 2 ? 1 : 2)) {
        if (x % p == 0) {
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            pr.pb(p);
            need.pb(cnt);
        }
    }
    if (x > 1) {
        pr.pb(x);
        need.pb(1);
    }
    int m = pr.size();
    int S = 1;
    vector<int> base(m);
    for (int i = 0; i < m; i++) {
        base[i] = need[i] + 1;
        S *= base[i];
    }
    vector<int> mul(m);
    for (int i = 0; i < m; i++) {
        mul[i] = (i == 0 ? 1 : mul[i - 1] * base[i - 1]);
    }
    vector<pair<int, vector<int>>> rows;
    rows.reserve(n - 1);
    for (int i = 1; i <= n - 1; i++) {
        char ch = s[i - 1];
        vector<int> opts;
        if (ch == '1')
            opts.pb(2);
        else if (ch == '0')
            opts.pb(i - 1);
        else {
            opts.pb(2);
            opts.pb(i - 1);
        }
        vector<pair<int, vector<int>>> row;
        for (int v : opts) {
            vector<int> e(m);
            ll y = v;
            for (int j = 0; j < m; j++) {
                int cnt = 0;
                while (y % pr[j] == 0 && cnt < need[j]) {
                    y /= pr[j];
                    cnt++;
                }
                e[j] = cnt;
            }
            row.pb({v, e});
        }
        rows.pb(row[0]);
        if (row.size() == 1)
            rows.back() = row[0];
        else
            rows.back() = row[1];
    }
    vector<vector<pair<int, vector<int>>>> olst;
    for (int i = 1; i <= n - 1; i++) {
        char ch = s[i - 1];
        vector<int> vals;
        if (ch == '1')
            vals = {2};
        else if (ch == '0')
            vals = {i - 1};
        else
            vals = {2, i - 1};
        vector<pair<int, vector<int>>> r;
        for (int v : vals) {
            vector<int> e(m);
            ll y = v;
            for (int j = 0; j < m; j++) {
                int cnt = 0;
                while (y % pr[j] == 0 && cnt < need[j]) {
                    y /= pr[j];
                    cnt++;
                }
                e[j] = cnt;
            }
            r.pb({v, e});
        }
        olst.pb(r);
    }
    if (s[0] == '?') {
        olst[0].clear();
        olst[0].pb({2, vector<int>(m, 0)});
        ll y = 2;
        for (int j = 0; j < m; j++) {
            int cnt = 0;
            while (y % pr[j] == 0 && cnt < need[j]) {
                y /= pr[j];
                cnt++;
            }
            olst[0][0].se[j] = cnt;
        }
    }
    vector<ld> lg(S, INF);
    vector<ll> md(S, 0);
    lg[0] = 0.0;
    md[0] = 1;
    vector<int> active;
    active.pb(0);
    vector<char> inact(S, 0);
    inact[0] = 1;
    for (int idx = 0; idx < olst.size(); ++idx) {
        auto &vec = olst[idx];
        vector<ld> nlg(S, INF);
        vector<ll> nmd(S, 0);
        vector<int> nact;
        nact.reserve(S);
        for (int sidx = 0; sidx < S; sidx++) {
            if (lg[sidx] == INF)
                continue;
            ld clg = lg[sidx];
            ll cur = md[sidx];
            for (auto &op : vec) {
                int v = op.fi;
                auto &ev = op.se;
                int nid = 0;
                for (int j = 0; j < m; j++) {
                    int cur = (sidx / mul[j]) % base[j];
                    int nu = cur + ev[j];
                    if (nu > need[j])
                        nu = need[j];
                    nid += nu * mul[j];
                }
                ld nl = clg + (v > 0 ? log((ld)v) : INF);
                ll nm = (cur * (v % MOD)) % MOD;
                if (nl + eps < nlg[nid] || (fabsl(nl - nlg[nid]) < eps && nm < nmd[nid])) {
                    nlg[nid] = nl;
                    nmd[nid] = nm;
                    if (!inact[nid]) {
                        nact.pb(nid);
                        inact[nid] = 1;
                    }
                }
            }
        }
        for (int id : active)
            inact[id] = 0;
        for (int id : nact)
            inact[id] = 0;
        lg.swap(nlg);
        md.swap(nmd);
        active.swap(nact);
    }
    bool f = false;
    ld mnlg = INF;
    ll mn = 0;
    for (int id = 0; id < S; id++) {
        if (lg[id] == INF)
            continue;
        bool ok = false;
        for (int j = 0; j < m; j++) {
            int cur = (id / mul[j]) % base[j];
            if (cur < need[j]) {
                ok = true;
                break;
            }
        }
        if (ok) {
            if (!f || lg[id] + eps < mnlg || (fabsl(lg[id] - mnlg) < eps && md[id] < mn)) {
                f = true;
                mnlg = lg[id];
                mn = md[id];
            }
        }
    }
    if (!f)
        cout << "-1" << endl;
    else
        cout << (mn % MOD) << "\n";
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