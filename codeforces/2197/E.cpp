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
// #define endl "\n"
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

void init() {
}

void solve() {
    int n;
    cin >> n;

    ll K = 1, idx = -1;
    vector<int> last;
    vector<PII> edges;
    vector<ll> memo(n + 1, -1);

    auto ask = [&](ll k) {
        cout << "? " << k << endl;
        int len;
        cin >> len;
        if (len == -1)
            exit(0);
        last.clear();
        if (len > 0) {
            last.resize(len);
            for (int i = 0; i < len; ++i) {
                cin >> last[i];
            }
        }
        idx = k;
    };
    auto go = [&](const vector<int> &pref) {
        if (last.size() < pref.size())
            return false;
        for (int i = 0; i < (int)pref.size(); ++i) {
            if (last[i] != pref[i])
                return false;
        }
        return true;
    };

    function<ll(int, vector<int> &)> dfs = [&](int u, vector<int> &pref) {
        K++;
        ll cnt = 1;

        while (true) {
            if (idx != K) {
                ask(K);
            }

            if (last.empty() || !go(pref)) {
                break;
            }

            int v = last[pref.size()];

            edges.pb({u, v});

            if (memo[v] != -1) {
                cnt += memo[v];
                K += memo[v];
            } else {
                pref.pb(v);
                ll cv = dfs(v, pref);
                pref.pob();

                memo[v] = cv;
                cnt += cv;
            }
        }
        return cnt;
    };

    for (int i = 1; i <= n; ++i) {
        if (memo[i] != -1) {
            K += memo[i];
        } else {
            vector<int> pref = {i};
            memo[i] = dfs(i, pref);
        }
    }

    cout << "! " << edges.size() << endl;
    for (auto [u, v] : edges) {
        cout << u << " " << v << endl;
    }
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