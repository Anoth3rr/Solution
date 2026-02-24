// Problem: 小红的字符串构造（hard）
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/126611/G
// Memory Limit: 512 MB
// Time Limit: 2000 ms
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
constexpr int maxn = 2e5;

struct Trie {
    vector<array<int, 2>> ch;
    vector<int> end, fa, val;
    int idx = 0;

    Trie(int n) : ch(n), end(n), fa(n), val(n) {}

    void insert(string s) {
        int u = 0;
        for (char c : s) {
            int v = c - '0';
            if (!ch[u][v]) {
                ch[u][v] = ++idx;
                ch[idx][0] = ch[idx][1] = 0;
                end[idx] = 0;
                fa[idx] = u;
                val[idx] = v;
            }
            u = ch[u][v];
        }
        end[u]++;
    }

    int find(int u, int cur, int k) {
        cur += end[u];

        if (cur == k && u != 0) {
            return u;
        }

        if (cur > k) {
            return -1;
        }

        for (int v = 0; v < 2; ++v) {
            if (ch[u][v]) {
                int res = find(ch[u][v], cur, k);
                if (res != -1)
                    return res;
            }
        }

        return -1;
    }
    string get(int u) {
        string res = "";
        while (u > 0) {
            res += to_string(val[u]);
            u = fa[u];
        }
        reverse(all(res));
        return res;
    }
};

void init() {}

void solve() {
    int n, k;
    cin >> n >> k;
    Trie tr(maxn);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        tr.insert(s);
    }

    int tar = tr.find(0, 0, k);

    if (tar != -1) {
        cout << tr.get(tar) << endl;
    } else {
        cout << -1 << endl;
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