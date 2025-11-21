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

int dx[] = {1, 1, -1, -1, 2, 2, -2, -2}, dy[] = {2, -2, 2, -2, 1, -1, 1, -1};

void init() {

}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    auto check = [&](int x, int y) -> bool{
        return 1 <= x && x <= n && 1 <= y && y <= m;
    };
    auto encode = [&](int x, int y) {
        return (x - 1) * m + (y - 1);
    };
    auto decode = [&](int id)->PII{
        return {id / m + 1, id % m + 1};
    };
    int s = encode(x1, y1), t = encode(x2, y2);

    vector<int> dist(n * m, -1), par(n * m, -1);
    queue<int> q;

    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        auto [x, y] = decode(u);
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!check(nx, ny)) continue;
            int v = encode(nx, ny);
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                par[v] = u;
                q.push(v);
            }
        }
    }
    if (dist[t] == -1 || k < dist[t] || ((k - dist[t]) & 1)) {
        cout << "No" << "\n";
        return;
    }

    if (dist[t] == 0) {
        if (k == 0) {
            cout << "Yes" << "\n";
            return;
        }
        int f = -1;
        auto [sx, sy] = decode(s);
        for (int i = 0; i < 8; i++) {
            int nx = sx + dx[i];
            int ny = sy + dy[i];
            if (check(nx, ny)) {
                f = encode(nx, ny);
                break;
            }
        }
        if (f == -1) {
            cout << "No" << "\n";
            return;
        }
        cout << "Yes" << "\n";
        int cycles = k / 2;
        for (int i = 0; i < cycles; i++) {
            auto p1 = decode(f);
            cout << p1.fi << " " << p1.se << "\n";
            auto p2 = decode(s);
            cout << p2.fi << " " << p2.se << "\n";
        }
        return;
    }

    cout << "Yes" << "\n";

    vector<int> ans;
    int cur = t;
    while (cur != -1) {
        ans.pb(cur);
        cur = par[cur];
    }
    reverse(all(ans));
    int d = ans.size() - 1;
    int c = (k - d) / 2;

    for (int i = 1; i < ans.size(); i++) {
        auto [u, v] = decode(ans[i]);
        cout << u << " " << v << "\n";
    }
    auto [u1, v1] = decode(ans[ans.size() - 2]);
    auto [u2, v2] = decode(ans[ans.size() - 1]);
    for (int i = 0; i < c; i++) {
        cout << u1 << " " << v1 << "\n";
        cout << u2 << " " << v2 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    init();

    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    return 0;
}
