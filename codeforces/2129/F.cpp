#include<bits/stdc++.h>
using namespace std;

vector<int> ask(int type, const vector<int>& idxs) {
    if (idxs.empty()) {
        return {};
    }
    cout << type << " " << idxs.size();
    for (int idx : idxs) {
        cout << " " << idx;
    }
    cout << endl;

    int k;
    if (type <= 2) {
        k = min(60, (int)idxs.size());
    } else {
        k = min(300, (int)idxs.size());
    }

    vector<int> res(k);
    if (k > 0) {
        for (int i = 0; i < k; ++i) {
            cin >> res[i];
        }
    }
    return res;
}

void solve() {
    int n;
    cin >> n;

    const int BS = max(1, (n + 14) / 15);
    int num_b = (n + BS - 1) / BS;

    vector<vector<int>> vib(num_b);
    for (int j = 0; j < num_b; ++j) {
        vector<int> idx_b;
        int st = j * BS + 1;
        int ed = min((j + 1) * BS, n);
        for (int i = st; i <= ed; ++i) {
            idx_b.push_back(i);
        }
        vib[j] = ask(1, idx_b);
    }

    vector<set<int>> pibs(num_b);
    for (int j = 0; j < num_b; ++j) {
        vector<int> val_b;
        int st = j * BS + 1;
        int ed = min((j + 1) * BS, n);
        for (int v = st; v <= ed; ++v) {
            val_b.push_back(v);
        }
        vector<int> p_res = ask(2, val_b);
        pibs[j] = set<int>(p_res.begin(), p_res.end());
    }

    vector<int> p(n + 1, 0);
    vector<int> pos(n + 1, 0);
    vector<set<int>> p_cand(n + 1);
    vector<set<int>> pos_cand(n + 1);

    for (int i = 1; i <= n; ++i) {
        int idx1 = (i - 1) / BS;
        for (int val : vib[idx1]) {
            int idx2 = (val - 1) / BS;
            if (pibs[idx2].count(i)) {
                p_cand[i].insert(val);
                pos_cand[val].insert(i);
            }
        }
    }

    queue<pair<int, int>> q;
    for (int i = 1; i <= n; ++i) {
        if (p_cand[i].size() == 1) {
            q.push({i, *p_cand[i].begin()});
        }
    }

    while (!q.empty()) {
        auto [cur_i, cur_v] = q.front();
        q.pop();

        if (p[cur_i] != 0) continue;

        p[cur_i] = cur_v;
        pos[cur_v] = cur_i;

        for (int i = 1; i <= n; ++i) {
            if (p[i] == 0 && p_cand[i].count(cur_v)) {
                p_cand[i].erase(cur_v);
                if (p_cand[i].size() == 1) {
                    q.push({i, *p_cand[i].begin()});
                }
            }
        }
        for (int v = 1; v <= n; ++v) {
            if (pos[v] == 0 && pos_cand[v].count(cur_i)) {
                pos_cand[v].erase(cur_i);
                if (pos_cand[v].size() == 1) {
                    q.push({*pos_cand[v].begin(), v});
                }
            }
        }
    }

    cout << "!";
    for (int i = 1; i <= n; ++i) {
        cout << " " << p[i];
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.flush();
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}