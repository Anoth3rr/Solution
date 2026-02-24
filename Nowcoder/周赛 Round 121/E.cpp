//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef __int128 i128;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef tuple<ll, ll, ll> TLLL;
typedef __gnu_pbds::tree<PLL, __gnu_pbds::null_type, less<PLL>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;
// typedef __gnu_pbds::tree<ll, __gnu_pbds::null_type, less<ll>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ld PI = acos(-1.0);
constexpr ld eps = 1e-10;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

struct State {
    int x, y, p, m;
};

void init() {

}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<vector<bool>>> gst(2, vector<vector<bool>>(n + 1, vector<bool>(m + 1)));

    for (int i = 0; i < k; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        gst[1][x1][y1] = true;
        gst[0][x2][y2] = true;
    }

    auto encode = [&](int x, int y, int p, int mod) -> int {
        return ((x * (m + 1) + y) * 2 + p) * 3 + mod;
    };

    int N = (n + 1) * (m + 1) * 2 * 3;
    vector<int> dist(N, -1);

    queue<State> q;

    dist[encode(1, 1, 1, 0)] = 0;
    q.push({1, 1, 1, 0});

    int ans = -1;

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        int x = cur.x, y = cur.y, p = cur.p, mode = cur.m;
        int d = dist[encode(x, y, p, mode)];

        if (x == n && y == m) {
            ans = d;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;

            if (mode != 1) {
                int np = 1 - p;
                int nm = (mode == 2 ? 2 : 0);
                if (!gst[np][nx][ny]) {
                    int idx = encode(nx, ny, np, nm);
                    if (dist[idx] == -1) {
                        dist[idx] = d + 1;
                        q.push({nx, ny, np, nm});
                    }
                }
            }
            if (mode == 0) {
                int np = 1 - p;
                int nm = 1;
                if (!gst[p][nx][ny]) {
                    int idx = encode(nx, ny, np, nm);
                    if (dist[idx] == -1) {
                        dist[idx] = d + 1;
                        q.push({nx, ny, np, nm});
                    }
                }
            }

            if (mode == 1) {
                int np = 1 - p;
                int nm = 2;
                if (!gst[1 - p][nx][ny]) {
                    int idx = encode(nx, ny, np, nm);
                    if (dist[idx] == -1) {
                        dist[idx] = d + 1;
                        q.push({nx, ny, np, nm});
                    }
                }
            }
        }
    }

    cout << ans << "\n";
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