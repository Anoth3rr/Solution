// Problem: 小L的三角尺
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/120566/A
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

struct Node {
    ld val, nxt;
    int idx;

    bool operator<(const Node other) const {
        return val < other.val;
    }
};

void init() {
}

void solve() {
    int n, w;
    cin >> n >> w;
    vector<ll> a(n), b(n), cur(n);
    vector<ld> h(n);
    priority_queue<Node> pq;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        h[i] = sqrt(1.0l * a[i] * a[i] + 1.0l * b[i] * b[i]);
        if (b[i] > 0) {
            ld nxt = sqrt(1.0l * a[i] * a[i] + 1.0l * (b[i] - 1) * (b[i] - 1));
            ld gain = 1.0l * (2 * b[i] - 1) / (h[i] + nxt);
            pq.push({gain, nxt, i});
        }
    }
    while (w > 0 && !pq.empty()) {
        auto u = pq.top();
        pq.pop();
        int i = u.idx;
        cur[i]++;
        w--;
        h[i] = u.nxt;

        ll rem = b[i] - cur[i];
        if (rem > 0) {
            ld nxt = sqrt(1.0l * a[i] * a[i] + 1.0l * (rem - 1) * (rem - 1));
            ld gain = 1.0l * (2 * rem - 1) / (h[i] + nxt);
            pq.push({gain, nxt, i});
        }
    }

    ld sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += sqrt(1.0l * a[i] * a[i] + 1.0l * (b[i] - cur[i]) * (b[i] - cur[i]));
    }
    cout << sum << endl;
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