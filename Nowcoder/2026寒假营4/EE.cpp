#include <bits/stdc++.h>
using namespace std;

// Class to handle DP state and history for a specific grid size
struct Solver {
    int n, m;
    int max_k;
    int mask_limit;
    bool solved;

    // max_scores[k] stores the max danger value for k mines
    vector<int> max_scores;
    // end_masks[k] stores the mask at the last state to begin reconstruction
    vector<int> end_masks;

    // Packed history to reconstruct the solution.
    // We store 2 bits per state to recover the previous mask.
    // Indexing: (p * mask_limit * (max_k + 1) + mask * (max_k + 1) + k)
    vector<uint32_t> history_packed;

    Solver() : solved(false) {}

    void init(int _n, int _m) {
        if (solved)
            return;
        n = _n;
        m = _m;
        max_k = n * m;
        mask_limit = 1 << (m + 1);
        max_scores.assign(max_k + 1, -1);
        end_masks.assign(max_k + 1, -1);

        long long total_states = (long long)(n * m + 1) * mask_limit * (max_k + 1);
        // We need 2 bits per state. 32 bits hold 16 states.
        long long vec_size = (total_states + 15) / 16;
        history_packed.assign(vec_size, 0);

        run_dp();
        solved = true;
    }

    void set_history(long long idx, int val) {
        // val is 2 bits (0-3)
        int shift = (idx & 15) * 2;
        history_packed[idx >> 4] |= ((uint32_t)val << shift);
    }

    int get_history(long long idx) const {
        int shift = (idx & 15) * 2;
        return (history_packed[idx >> 4] >> shift) & 3;
    }

    long long get_idx(int p, int mask, int k) const {
        return (long long)p * mask_limit * (max_k + 1) + (long long)mask * (max_k + 1) + k;
    }

    void run_dp() {
        // dp[mask][k] stores max score at current step
        // Initialize with -1
        vector<vector<int>> dp(mask_limit, vector<int>(max_k + 1, -1));
        dp[0][0] = 0;

        for (int p = 0; p < n * m; ++p) {
            vector<vector<int>> next_dp(mask_limit, vector<int>(max_k + 1, -1));
            int r = p / m;
            int c = p % m;

            for (int mask = 0; mask < mask_limit; ++mask) {
                for (int k = 0; k <= max_k; ++k) {
                    if (dp[mask][k] == -1)
                        continue;

                    // Try putting 0 (empty) or 1 (mine)
                    for (int val = 0; val <= 1; ++val) {
                        if (k + val > max_k)
                            continue;

                        // Calc score contribution with neighbors
                        int score = 0;
                        // Neighbors in terms of mask bits:
                        // Left (r, c-1): bit c-1 (valid if c>0)
                        if (c > 0)
                            score += (val ^ ((mask >> (c - 1)) & 1));
                        // Top-Left (r-1, c-1): bit c (valid if r>0, c>0)
                        if (r > 0 && c > 0)
                            score += (val ^ ((mask >> c) & 1));
                        // Top (r-1, c): bit c+1 (valid if r>0)
                        if (r > 0)
                            score += (val ^ ((mask >> (c + 1)) & 1));
                        // Top-Right (r-1, c+1): bit c+2 (valid if r>0, c<m-1)
                        if (r > 0 && c < m - 1)
                            score += (val ^ ((mask >> (c + 2)) & 1));

                        int current_total = dp[mask][k] + score;
                        int nk = k + val;

                        // Determine next mask and history bits
                        int nmask = 0;
                        int history_val = 0;

                        if (c == m - 1) {
                            // End of row: Shift logic
                            // Temp update bit c (position m-1)
                            int tmp = mask;
                            if (val)
                                tmp |= (1 << c);
                            else
                                tmp &= ~(1 << c);

                            // Bits to store: old_m and old_c
                            // old_c is bit c of mask
                            // old_m is bit m of tmp
                            int old_c = (mask >> c) & 1;
                            int old_m = (tmp >> m) & 1;
                            history_val = (old_m << 1) | old_c;

                            // Shift: discard bit m, shift 0..m-1 to 1..m
                            nmask = (tmp & ((1 << m) - 1)) << 1;
                        } else {
                            // Normal logic
                            // We overwrite bit c with val
                            // History: just old bit c
                            int old_c = (mask >> c) & 1;
                            history_val = old_c; // old_m is 0 implicitly

                            nmask = mask;
                            if (val)
                                nmask |= (1 << c);
                            else
                                nmask &= ~(1 << c);
                        }

                        if (current_total >= next_dp[nmask][nk]) {
                            next_dp[nmask][nk] = current_total;
                            long long idx = get_idx(p + 1, nmask, nk);
                            set_history(idx, history_val);
                        }
                    }
                }
            }
            dp = move(next_dp);
        }

        // Store results
        for (int mask = 0; mask < mask_limit; ++mask) {
            for (int k = 0; k <= max_k; ++k) {
                if (dp[mask][k] > max_scores[k]) {
                    max_scores[k] = dp[mask][k];
                    end_masks[k] = mask;
                }
            }
        }
    }
};

Solver cache[10][10];

int main() {
    freopen("1.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int N = 1; N <= 9; ++N) {
        for (int M = 1; M <= 9; ++M) {
            for (int K = 0; K <= N * M; ++K) {
                cout << "if(n==" << N << "||m==" << M << "||k==" << K << "){" << endl;
                int n = N, m = M, k = K;
                cout << "cout<<";
                bool swapped = false;
                // Ensure m is the smaller dimension for efficiency
                if (n < m) {
                    swap(n, m);
                    swapped = true;
                }

                // Init/Run DP if needed
                cache[n][m].init(n, m);
                Solver &sol = cache[n][m];

                cout << sol.max_scores[k] << "<<endl;"
                     << "\n";

                // Reconstruct grid
                vector<string> grid(n, string(m, '.'));

                int cur_mask = sol.end_masks[k];
                int cur_k = k;

                // Backtrack from p = n*m down to 1
                for (int p = n * m; p > 0; --p) {
                    int r = (p - 1) / m;
                    int c = (p - 1) % m;

                    long long idx = sol.get_idx(p, cur_mask, cur_k);
                    int h_val = sol.get_history(idx);

                    int val = 0;
                    int prev_mask = 0;

                    if (c == m - 1) {
                        // Reverse shift logic
                        // val is at bit m of cur_mask
                        val = (cur_mask >> m) & 1;

                        int old_m = (h_val >> 1) & 1;
                        int old_c = h_val & 1;

                        // Recover tmp
                        int tmp_low = cur_mask >> 1;
                        int tmp = tmp_low | (old_m << m);

                        // Recover prev_mask from tmp (restore bit c)
                        prev_mask = tmp;
                        if (old_c)
                            prev_mask |= (1 << c);
                        else
                            prev_mask &= ~(1 << c);
                    } else {
                        // Reverse normal logic
                        // val is at bit c of cur_mask
                        val = (cur_mask >> c) & 1;

                        int old_c = h_val & 1;
                        prev_mask = cur_mask;
                        if (old_c)
                            prev_mask |= (1 << c);
                        else
                            prev_mask &= ~(1 << c);
                    }

                    if (val)
                        grid[r][c] = '*';

                    cur_mask = prev_mask;
                    cur_k -= val;
                }

                // Output
                if (swapped) {
                    for (int j = 0; j < m; ++j) {
                        cout << "cout<<\"";
                        for (int i = 0; i < n; ++i) {
                            cout << grid[i][j];
                        }
                        cout << "\"<<endl;"
                             << "\n";
                    }
                } else {
                    for (int i = 0; i < n; ++i) {
                        cout << "cout<<\"";
                        cout << grid[i] << "\"<<endl;"
                             << "\n";
                    }
                }
                cout << "}";
            }
        }
    }

    return 0;
}