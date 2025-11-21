//Anoth3r
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

int dx[] = { -1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
int A[] = {0, 1, 2, 3}, B[] = {3, 2, 1, 0}, C[] = {1, 0, 3, 2};

void init() {

}

void solve() {
    int h, w;
    cin >> h >> w;
    vector<string> g(h);
    for (int i = 0; i < h; ++i) cin >> g[i];

    if (h == 0 || w == 0) {
        cout << 0 << "\n";
        return;
    }

    vector<int> dist(h * w * 4, inf);

    auto encode = [&](int i, int j, int d) -> int{
        return (i * w + j) * 4 + d;
    };

    auto check = [&](int x, int y) -> bool{
        return 0 <= x && x < h && 0 <= y && y < w;
    };

    deque<array<int, 3>> dq;

    dist[encode(0, 0, 1)] = 0;
    dq.push_back({0, 0, 1});
    int ans = inf;
    while (dq.size()) {
        auto [x, y, d] = dq.front();
        dq.pop_front();
        int id = encode(x, y, d);

        if (dist[id] >= ans) continue;

        int mp[4];
        if (g[x][y] == 'A') {
            for (int i = 0; i < 4; ++i) mp[i] = A[i];
        } else if (g[x][y] == 'B') {
            for (int i = 0; i < 4; ++i) mp[i] = B[i];
        } else {
            for (int i = 0; i < 4; ++i) mp[i] = C[i];
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nid = encode(nx, ny, i);
            int cost = (i == mp[d]) ? 0 : 1;

            if (check(nx, ny)) {
                if (dist[id] + cost < dist[nid]) {
                    dist[nid] = dist[id] + cost;
                    if (cost == 0) dq.push_front({nx, ny, i});
                    else dq.push_back({nx, ny, i});
                }
            } else {
                if (x == h - 1 && y == w - 1 && i == 1) {
                    ans = min(ans, dist[id] + cost);
                }
            }
        }
    }
    if (ans == inf) ans = -1;
    cout << ans << "\n";
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
