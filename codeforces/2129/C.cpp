#include <bits/stdc++.h>
using namespace std;

int calc_f(const string& t, vector<int>& suf_cnt) {
    int n = t.length();
    suf_cnt.assign(n, 0);
    if (n == 0) return 0;

    stack<int> st;
    vector<int> match(n, -1);
    for (int i = 0; i < n; ++i) {
        if (t[i] == '(') {
            st.push(i);
        } else if (!st.empty()) {
            match[i] = st.top();
            st.pop();
        }
    }

    int total_f = 0;
    for (int i = 0; i < n; ++i) {
        if (t[i] == ')' && match[i] != -1) {
            int j = match[i];
            suf_cnt[i] = 1;
            if (j > 0) {
                suf_cnt[i] += suf_cnt[j - 1];
            }
        }
        total_f += suf_cnt[i];
    }
    return total_f;
}

void solve() {
    int n;
    cin >> n;

    string ans(n, ' ');
    vector<int> idx_q;

    ans[0] = '(';
    idx_q.push_back(1);

    string cp = "(";
    int f_prev = 0;
    vector<int> suf_cnt;

    for (int k = 2; k <= n; ++k) {
        string p_o = cp + '(';
        vector<int> suf_o;
        int f_o = calc_f(p_o, suf_o);
        int d_o = f_o - f_prev;

        string p_c = cp + ')';
        vector<int> suf_c;
        int f_c = calc_f(p_c, suf_c);
        int d_c = f_c - f_prev;

        idx_q.push_back(k);
        cout << "? " << idx_q.size();
        for (int idx : idx_q) cout << " " << idx;
        cout << endl;

        int f_curr;
        cin >> f_curr;
        int d_real = f_curr - f_prev;

        if (d_real == d_o) {
            ans[k - 1] = '(';
            cp = p_o;
            f_prev = f_o;
        } else {
            ans[k - 1] = ')';
            cp = p_c;
            f_prev = f_c;
        }
    }

    int first_close_idx = -1;
    for (int i = 0; i < n; ++i) {
        if (ans[i] == ')') {
            first_close_idx = i + 1;
            break;
        }
    }

    if (first_close_idx == -1) {
        for (char& c : ans) c = ')';
    } else {
        cout << "? 4 1 " << first_close_idx << " 1 " << first_close_idx << endl;
        int res;
        cin >> res;
        if (res == 1) {
            for (char& c : ans) c = (c == '(') ? ')' : '(';
        }
    }

    cout << "! " << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
