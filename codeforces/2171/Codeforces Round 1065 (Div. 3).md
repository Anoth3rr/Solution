# A Shizuku Hoshikawa and Farm Legs

鸡兔同笼小问题。

先检查奇偶性，奇数无解。

设鸡 $x$ ，牛 $y$ ，$2x+4y=n$

所以有 $x = (n-4y)/2 \geq 0$

得到 $y\leq n/4$

所以方案数为 $\lfloor\frac{n}{4}\rfloor+1$

```cpp
void solve() {
    ll n;
    cin >> n;

    if (n % 2 != 0) {
        cout << 0 << "\n";
    } else {
        cout << n / 4 + 1 << "\n";
    }
}
```

# B Yuu Koito and Minimum Absolute Sum

差分数组的和是一个裂项相消的过程：
$$
\sum\limits_{i=1}^{n-1}(a_{i+1}-a_i)=a_n-a_1
$$
因此目标是最小化 $|an−a1|$ 。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (a[0] != -1 && a[n - 1] == -1) {
        a[n - 1] = a[0];
    } else if (a[0] == -1 && a[n - 1] != -1) {
        a[0] = a[n - 1];
    } else if (a[0] == -1 && a[n - 1] == -1) {
        a[0] = 0;
        a[n - 1] = 0;
    }

    for (int i = 1; i < n - 1; ++i) {
        if (a[i] == -1) {
            a[i] = 0;
        }
    }

    cout << abs(a[n - 1] - a[0]) << "\n";
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    cout << "\n";
}
```

# C Renako's XOR Game

无论是否交换，位置 $i$ 对总异或差 $K=(\oplus A)\oplus(\oplus B)$ 的贡献始终是 $a_i\oplus b_i$ 。因此最终两人的异或和之差的位模式 $K$ 是固定的。

- 如果 $K=0$，两数相等，必平局。
- 如果 $K\neq0$ ，胜负取决于 $K$ 的最高有效位。谁在该位上是 $1$ ，谁就赢。

策略：

- 只有在 $ai\oplus bi$ 的为 $1$ 的回合，玩家的操作才能改变最终结果在该位的状态。
- 归纳：最后一个拥有改变最高有效位权利的玩家（即最大的 $i$ 满足 $(a_i\oplus b_i)$ 在最高有效位为 1）决定了最终结果。因为无论前面怎么操作，最后这个人总能选择让自己赢的操作。
- 如果该 $i$ 是奇数回合，$Ajisai$ 胜；如果是偶数回合，$Mai$ 胜。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    int K = 0;
    for (int i = 0; i < n; ++i) {
        K ^= (a[i] ^ b[i]);
    }

    if (K == 0) {
        cout << "Tie" << "\n";
        return;
    }

    int msb = 0;
    for (int k = 20; k >= 0; --k) {
        if ((K >> k) & 1) {
            msb = k;
            break;
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        if (((a[i] >> msb) & 1) != ((b[i] >> msb) & 1)) {
            if ((i + 1) % 2 != 0) {
                cout << "Ajisai" << "\n";
            } else {
                cout << "Mai" << "\n";
            }
            return;
        }
    }
}
```

# D/F Rae Taylor and Trees

1. **连通性判定 (Easy)**：
   - 如果存在一个分割点 $i$ ，使得排列的前缀 $p[0…i]$ 的最小值 大于 后缀 $p[i+1…n−1]$ 的最大值，说明左边所有元素都比右边大。
   - 由于题目要求连边 $(u,v)$ 必须满足 $u<v$ 且 $pos[u]<pos[v]$ ，这种情况下左边没法连向右边，图不连通。
   - 判定方法：遍历数组，若 $min⁡(pref)>max⁡(rem,suff)$ ，则输出 "No"。
2. **构造方案 (Hard)**：
   - **寻找骨干**：找出排列中所有的前缀最小值。这些点将排列分成了若干段。
   - **组内连接**：对于每一段内非前缀最小值的元素 $x$ ，它一定大于该段的前缀最小值 $mn$ ，且位置在后，直接连边 $(mn,x)$ 。
   - **组间连接**：将当前的前缀最小值连向右侧剩余后缀中的最大值。
     - 因为通过了判定，所以 $mn<max(suff)$ ，且 $mn$ 位置在 $mx$ 之前，满足条件。
     - 这样所有段都被串联起来形成一棵树。

D：

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    vector<int> suff(n);
    suff[n - 1] = p[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        suff[i] = max(suff[i + 1], p[i]);
    }

    int prev = p[0];
    for (int i = 0; i < n - 1; ++i) {
        prev = min(prev, p[i]);

        if (prev > suff[i + 1]) {
            cout << "No" << "\n";
            return;
        }
    }

    cout << "Yes" << "\n";
}
```

F：

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    vector<int> suff(n);
    suff[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; --i) {
        if (p[i] > p[suff[i + 1]]) {
            suff[i] = i;
        } else {
            suff[i] = suff[i + 1];
        }
    }

    vector<int> pref;
    int mn = n + 1;
    for (int i = 0; i < n; ++i) {
        if (p[i] < mn) {
            mn = p[i];
            pref.pb(i);
        }
    }

    for (int k = 0; k < pref.size() - 1; ++k) {
        if (p[pref[k]] > p[suff[pref[k + 1]]]) {
            cout << "No" << "\n";
            return;
        }
    }

    cout << "Yes" << "\n";

    int cur = 0;
    for (int i = 1; i < n; ++i) {
        if (cur + 1 < pref.size() && i == pref[cur + 1]) {
            cur++;
        } else {
            cout << p[pref[cur]] << " " << p[i] << "\n";
        }
    }

    for (int k = 0; k < pref.size() - 1; ++k) {
        cout << p[pref[k]] << " " << p[suff[pref[k + 1]]] << "\n";
    }
}
```

# E Anisphia Wynn Palettia and Good Permutations

我们要极力避免“三个两两互质的数连在一起”。

1. **分类**：
   - 3的倍数：$gcd\geq 3$ ，内部连接。
   - 坏数：$1$ 和 大于 $n/2$ 的素数。它们与别的数没有公因数。
   - 偶数：$gcd⁡\geq2$ ，是连接的骨架。
   - 其余奇数：可以挂在 $2\times spf[x]$ 的偶数上。
2. 构造：
   - 簇：将 $Odd$ 挂在对应的 $Even$ 上，形成 $[Odd, Odd..., Even]$ 的结构。这些 $Even$ 称为“忙碌偶数”。
   - 骨架：由 $S3$ 序列（奇数倍 $3$ -> 偶数倍 $3$ ）和“空闲偶数”组成。这个序列内部相邻元素都有公因数。
   - 插入坏数：将坏数插入到骨架中，只能插在 $u,v$ 之间，且满足 $gcd(u,v)>1$ ，这样形成 $(u,Bad,v)$ 。
     - 间隔插入：避免 $(Bad,u,Bad)$ 的情况，采用插一个跳一个的策略。
   - 最后接上“忙碌偶数簇”。

```cpp
vector<int> primes, spf(maxn + 1);

void init() {
    for (int i = 2; i <= maxn; ++i) {
        if (!spf[i]) primes.push_back(i), spf[i] = i;
        for (int j = 0; primes[j]*i <= maxn; ++j) {
            int m = primes[j] * i;
            spf[m] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
}

void solve() {
    int n;
    cin >> n;

    vector<int> s3_odd, s3_even;
    vector<int> bad;
    vector<int> odd;
    vector<int> even;

    for (int i = 1; i <= n; ++i) {
        if (i % 3 == 0) {
            if (i % 2 == 0) s3_even.pb(i);
            else s3_odd.pb(i);
        } else if (i == 1) {
            bad.pb(i);
        } else if (i % 2 == 0) {
            even.pb(i);
        } else {
            if (spf[i] == i && i > n / 2) {
                bad.pb(i);
            } else {
                odd.pb(i);
            }
        }
    }

    map<int, vector<int>> clu;
    for (int x : odd) {
        int target = 2 * spf[x];
        if (target > n) {
            bad.pb(x);
        } else {
            clu[target].pb(x);
        }
    }

    vector<int> occ, flx;
    for (int e : even) {
        if (clu.count(e)) occ.pb(e);
        else flx.pb(e);
    }

    vector<int> bb;
    for (int x : s3_odd) bb.pb(x);
    for (int x : s3_even) bb.pb(x);
    for (int x : flx) bb.pb(x);

    vector<int> main;
    int b_idx = 0;
    bool f = false;

    if (!bb.empty()) {
        main.pb(bb[0]);
    }

    for (int i = 0; i < (int)bb.size() - 1; ++i) {
        int u = bb[i];
        int v = bb[i + 1];

        bool ins = false;
        if (b_idx < bad.size() && !f) {
            if (__gcd(u, v) > 1) {
                main.pb(bad[b_idx++]);
                f = true;
                ins = true;
            }
        }

        if (!ins) {
            f = false;
        }

        main.pb(v);
    }

    while (b_idx < bad.size()) {
        main.pb(bad[b_idx++]);
    }

    for (int e : occ) {
        main.pb(e);
        for (int o : clu[e]) {
            main.pb(o);
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << main[i] << " ";
    }
    cout << "\n";
}
```

# G Sakura Adachi and Optimal Sequences

假设总共进行了 $K$ 次翻倍。对于每个元素 $i$ ，最终值 $b_i$ 可以表示为：
$$
b_i = a_i\cdot 2^K+\sum\limits_{j=0}^Kc_{i,j}\cdot2^j
$$
其中 $c_{i,j}$ 是在倒数第 $j$ 次翻倍操作之后（即权重为 $2^j$ 的阶段）对 $a_i$ 进行的加 $1$ 操作次数。

总操作数 $x=K+\sum_{i,j}c_{i,j}$ 。

为了最小化 $x$ ，我们应该贪心地利用高位。

- 对于 $0\leq j<K$ ，系数 $c_{i,j}$ 应当等于 $b_i$ 二进制表示的第 $j$ 位（0 或 1）。这是因为在低位加 2 次不如在高位加 1 次划算。
- 对于 $j=K$（即所有翻倍之前），$c_{i,K}$ 承担剩余的差值：$c_{i,K}=(b_i≫K)−a_i$ 。
- 如果对于任意 $i$ ， $(b_i≫K)<a_i$ ，则说明该 $K$ 不可行。

对于确定的 $K$ ，每个阶段 $j$ 的总加法操作数 $S_j=\sum_{i}c_{i,j}$ 是固定的。

- 阶段 $j$ 的操作序列是将 $S_j$ 个操作分配给不同的 $i$ ，这是一个多项式系数问题。该阶段的方案数为 $\frac{S_j!}{\prod_ic_{i,j}!}$ 。
- 不同阶段之间被“翻倍”操作隔开，因此总方案数是各阶段方案数的乘积。

```cpp
void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    vector<int> cnt(22, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= 20; ++j) {
            if ((b[i] >> j) & 1) cnt[j]++;
        }
    }

    int lim = 20;

    ll ans = -1;
    Z tot = 0;

    for (int K = 0; K <= lim; ++K) {
        ll ops = K;

        bool ok = true;
        ll sk = 0;
        for (int i = 0; i < n; ++i) {
            int val = (b[i] >> K);
            if (val < a[i]) {
                ok = false;
                break;
            }
            sk += (val - a[i]);
        }
        if (!ok) continue;

        for (int j = 0; j < K; ++j) ops += cnt[j];
        ops += sk;

        Z cur = 1;

        for (int j = 0; j < K; ++j) {
            cur *= C.fac(cnt[j]);
        }
        if (sk >= MOD) {
            cur = 0;
        } else {
            cur *= C.fac((int)sk);
        }

        if (cur.val() != 0) {
            for (int i = 0; i < n; ++i) {
                int cnt = (b[i] >> K) - a[i];
                cur *= C.inv(cnt);
            }
        }

        if (ans == -1 || ops < ans) {
            ans = ops;
            tot = cur;
        } else if (ops == ans) {
            tot += cur;
        }
    }

    cout << ans << " " << tot << "\n";
}
```

# H Shiori Miyagi and Maximum Array Score

只有当 $i\mid x$ 时，$v(i,x)>0$ 。否则 $v(i,x)=0$ 。

若想获得总和最大，只需要考虑那些能产生正贡献的选择。

我们从小到大枚举所有值 $x=1..m$ ，决定是否把 $x$ 作为第 $i$ 个选入的数。

设 $dp[i]$ 为 当前考虑到 $x$ 为止，已选 $i$ 个数时能获得的最大值。

初始：$dp[0]=0$ ，其他设为 $-\infin$ 。

当枚举到某个 $x$ ：

只需要遍历 $x$ 的约数 $d$（其中 $2 \leq d \leq n$ ）：

- 若把 $x$ 选为第 $d$ 个数，则：$dp[d] = \max(dp[d],\; dp[d-1] + v(d,x))$ 。

其中 $v(d,x)$ 就是不断让 $x/=d$ 的次数。

不用对所有 $d$ 做过渡，因为只有 $d\mid x$ 时才有正贡献；零贡献的“占位”可通过 $DP$ 中本身的非严格增长补上。

答案即为 $dp[n]$​ 。

```cpp
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> divs(m + 1);
    for (int d = 2; d <= n; ++d) {
        for (int x = d; x <= m; x += d) divs[x].pb(d);
    }
    vector<int> dp(n + 1, -inf), b(n + 1, -inf);
    dp[0] = 0; b[0] = 0;
    vector<vector<int>> sch(m + 2);


    for (int x = 1; x <= m; ++x) {
        bool f = false;
        if (x <= n && b[x] < 0) f = true;


        vector<int> updated;
        while (!sch[x].empty()) {
            int d = sch[x].back(); sch[x].pop_back();
            if (d > n) continue;
            int prev = b[d - 1];
            if (d - 1 == x && f) prev = 0;
            if (dp[d] < prev) {
                dp[d] = prev;
                updated.pb(d);
            }
        }
        for (int d : divs[x]) {
            int prev = b[d - 1];
            if (d - 1 == x && f) prev = 0;
            int k = 0;
            int xx = x;
            while (xx % d == 0) { xx /= d; ++k; }
            int val = prev == -inf ? -inf : prev + k;
            if (val > dp[d]) { dp[d] = val; updated.pb(d); }
        }
        for (int d : updated) {
            if (dp[d] > b[d]) {
                b[d] = dp[d];
                if (x + 1 <= m + 1) sch[x + 1].pb(d + 1);
            }
        }
        if (f) {
            if (b[x] < 0) {
                b[x] = 0;
                if (x + 1 <= m + 1) sch[x + 1].pb(x + 1);
            }
        }
    }
    int ans = max(0, b[n]);
    cout << ans << "\n";
}
```

