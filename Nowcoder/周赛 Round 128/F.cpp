// Problem: 小红的提拉米苏配方 （hard）
// Contest: NowCoder
// Url: https://ac.nowcoder.com/acm/contest/127240/F
// Memory limit: 512 MB
// Time limit: 2000 ms
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
using Pll = pair<ll, ll>;
using TIII = tuple<int, int, int>;
using Tlll = tuple<ll, ll, ll>;

void init() {
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> idx;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1')
            idx.pb(i);
    }
    vector<int> mark(n);
    int l = 0, r = idx.size() - 1, lst = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '2') {
            lst = i;
        } else if (s[i] == '0') {
            while (l <= r && idx[l] < lst) {
                l++;
            }

            while (l <= r && idx[l] < i) {
                if (idx[r] < i) {
                    break;
                }

                mark[idx[l]] = 1;
                mark[idx[r]] = 2;

                l++;
                r--;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (mark[i] == 1)
            continue;
        if (mark[i] == 2)
            cout << '2';
        else
            cout << s[i];
    }
    cout << endl;
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