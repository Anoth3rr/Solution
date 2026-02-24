// Problem: 小红的提拉米苏配方（easy）
// Contest: NowCoder
// URL: https://ac.nowcoder.com/acm/contest/127240/E
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

void init() {
}

void solve() {
    string s;
    cin >> s;
    int n = s.size(), pos = -1;
    vector<int> idx;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            idx.pb(i);
        }
    }
    vector<int> mark(n);
    if (!idx.size()) {
        cout << s << endl;
        return;
    }
    int cnt = idx.size() / 2, f = idx.size() & 1;
    for (int i = 0; i < cnt; ++i) {
        mark[idx.back()] = 2;
        idx.pob();
    }
    char p = '.';
    int ptr = idx.size() - 1;
    for (int i = n - 1; i >= 0;) {
        while (i >= 0 && i > idx[ptr]) {
            if (s[i] != '1')
                p = s[i];
            i--;
        }
        if (p == '2') {
            pos = i;
        }

        ptr--;
        if (ptr < 0)
            break;
    }
    if (f) {
        if (pos == -1)
            mark[idx.back()] = 1;
        else
            mark[pos] = 1;
    }
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            if (mark[i] == 2)
                cout << '2';
            else if (f && mark[i] == 1)
                cout << '1';
        } else {
            cout << s[i];
        }
    }
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