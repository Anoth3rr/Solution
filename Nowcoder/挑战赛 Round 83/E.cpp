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

template<class Int>
struct BIT {
    vector<Int> a;
    int n;

    BIT() {}
    BIT(int n) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        a.resize(n + 1);
    }

    void add(int x, int k) {
        for (; x <= n; x += x & -x) {
            a[x] += k;
        }
    }

    void add(int x, int y, Int k) {
        add(x, k), add(y + 1, -k);
    }

    Int ask(int x) {
        Int ans = 0;
        for (; x; x -= x & -x) {
            ans += a[x];
        }
        return ans;
    }

    Int ask(int x, int y) {
        return ask(y) - ask(x - 1);
    }

    Int kth(int k) {
        Int ans = 0;
        for (int i = __lg(n); i >= 0; i--) {
            Int val = ans + (1 << i);
            if (val < n && a[val] < k) {
                k -= a[val];
                ans = val;
            }
        }
        return ans + 1;
    }
};

void init() {

}

void solve() {
    int n;
    cin >> n;
    vector<array<int, 3>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        sort(all(a[i]));
    }
    vector<int> mx(n), sec(n);
    for (int i = 0; i < n; i++) {
        mx[i] = a[i][2];
        sec[i] = a[i][1];
    }
    vector<PII> vmx;
    for (int i = 0; i < n; i++) vmx.eb(mx[i], i);
    sort(all(vmx));
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        int idx = vmx[i].se;
        A[idx] = i;
    }

    vector<PII> vmmx;
    for (int i = 0; i < n; i++) vmmx.eb(sec[i], i);
    sort(all(vmmx));
    vector<int> B(n);
    for (int i = 0; i < n; ++i) {
        int idx = vmmx[i].se;
        B[idx] = i;
    }

    vector<int> mmx(n);
    for (int i = 0; i < n; i++) mmx[i] = sec[i];
    vector<int> sec2 = mmx;
    sort(all(sec2));
    sec2.erase(unique(all(sec2)), sec2.end());
    auto get = [&](int x) {
        return int(lower_bound(all(sec2), x) - sec2.begin()) + 1;
    };
    BIT<ll> bit((int)sec2.size());
    vector<int> both(n, 0);
    for (auto &pr : vmx) {
        int idx = pr.second;
        int sr = get(sec[idx]);
        if (sr - 1 >= 1) both[idx] = bit.ask(sr - 1);
        else both[idx] = 0;
        bit.add(sr, 1);
    }

    vector<ll> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = A[i] + B[i] - both[i];
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
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
