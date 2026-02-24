// Problem: 「SFCOI-4」生活在树上
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120679/C
// Memory Limit: 1024 MB
// Time Limit: 4000 ms
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

const int N = 100005;
int n;
ll k;
int a[N];
int L[N], R[N];
int _L[N], _R[N];
int ls[N], rs[N];
bool inq[N];

set<int> u_R, u_L;

void init() {}

int build(int l, int r, int p) {
    if (l > r) return 0;

    for (int d = 0; l + d <= r - d; ++d) {
        int cands[] = {l + d, r - d};
        for (int u : cands) {
            if (p && ((ll)a[u] ^ a[p]) > k) continue;

            if (L[u] <= l && R[u] >= r) {
                ls[u] = build(l, u - 1, u);
                rs[u] = build(u + 1, r, u);
                return u;
            }

            if (l + d == r - d) break;
        }
    }
    return 0;
}

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    for (int i = 0; i <= n + 1; ++i) {
        L[i] = R[i] = i;
        _L[i] = i + 1;
        _R[i] = i - 1;
        ls[i] = rs[i] = 0;
        inq[i] = false;
    }

    u_R.clear();
    u_L.clear();
    for (int i = 1; i <= n; ++i) {
        u_R.insert(i);
        u_L.insert(i);
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        q.push(i);
        inq[i] = true;
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;

        int start_p = L[u] - 1;
        int end_p = _L[u] - 2;

        if (start_p <= end_p) {
            auto it = u_R.lower_bound(start_p);
            while (it != u_R.end() && *it <= end_p) {
                int p = *it;
                if (((ll)a[u] ^ a[p]) <= k) {
                    if (R[u] > R[p]) {
                        R[p] = R[u];
                        if (!inq[p]) {
                            inq[p] = true;
                            q.push(p);
                        }

                        if (R[p] == n) {
                            it = u_R.erase(it);
                            continue;
                        }
                    }
                }
                ++it;
            }
        }
        _L[u] = L[u];

        start_p = _R[u] + 2;
        end_p = R[u] + 1;

        if (start_p <= end_p) {
            auto it = u_L.lower_bound(start_p);
            while (it != u_L.end() && *it <= end_p) {
                int p = *it;
                if (((ll)a[u] ^ a[p]) <= k) {
                    if (L[u] < L[p]) {
                        L[p] = L[u];
                        if (!inq[p]) {
                            inq[p] = true;
                            q.push(p);
                        }
                        if (L[p] == 1) {
                            it = u_L.erase(it);
                            continue;
                        }
                    }
                }
                ++it;
            }
        }
        _R[u] = R[u];
    }

    int root = -1;
    for (int i = 1; i <= n; ++i) {
        if (L[i] == 1 && R[i] == n) {
            root = i;
            break;
        }
    }

    if (root == -1) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl;
        ls[root] = build(1, root - 1, root);
        rs[root] = build(root + 1, n, root);
        for (int i = 1; i <= n; ++i) {
            cout << ls[i] << " " << rs[i] << endl;
        }
    }
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