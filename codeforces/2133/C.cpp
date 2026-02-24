//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(),a.rend()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef __int128 lll;
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

void init() {

}

void solve() {
    int n;
    cin >> n;

    vector<int> dist(n + 1);
    int st = -1;
    int mx = 0;

    for (int i = 1; i <= n; ++i) {
        cout << "? " << i << " " << n;
        for (int j = 1; j <= n; ++j) {
            cout << " " << j;
        }
        cout << endl;

        cin >> dist[i];

        if (dist[i] > mx) {
            mx = dist[i];
            st = i;
        }
    }

    vector<int> path;
    path.pb(st);
    vector<bool> vis(n + 1, false);
    vis[st] = true;

    int lst = st;

    while (path.size() < mx) {
        int cur = path.size();
        int tar = mx - cur;
        int nxt = -1;

        for (int i = 1; i <= n; ++i) {
            if (!vis[i] && dist[i] == tar) {
                cout << "? " << lst << " " << 2 << " " << lst << " " << i << endl;
                int res;
                cin >> res;

                if (res == 2) {
                    nxt = i;
                    break;
                }
            }
        }

        path.pb(nxt);
        vis[nxt] = true;
        lst = nxt;
    }

    cout << "! " << path.size();
    for (int v : path) {
        cout << " " << v;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    init();

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}