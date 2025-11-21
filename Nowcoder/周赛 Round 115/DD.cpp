#include <bits/stdc++.h>
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
using namespace std;
using ll = long long;

static const size_t IN_BUF_SZ = 1 << 20;
static char inbuf[IN_BUF_SZ];
static size_t in_pos = 0, in_len = 0;

static inline int getchar_() __attribute__((always_inline));
static inline int getchar_() {
    if (in_pos >= in_len) {
        in_len = fread(inbuf, 1, IN_BUF_SZ, stdin);
        in_pos = 0;
        if (in_len == 0) return EOF;
    }
    return inbuf[in_pos++];
}

static inline ll rd() __attribute__((always_inline));
static inline ll rd() {
    int c = getchar_();
    while (__builtin_expect((c != '-') && (c < '0' || c > '9'), 1)) {
        c = getchar_();
        if (c == EOF) return 0;
    }
    int neg = 0;
    if (c == '-') { neg = 1; c = getchar_(); }
    ll x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar_();
    }
    return neg ? -x : x;
}

static const size_t OUT_BUF_SZ = 1 << 20;
static char outbuf[OUT_BUF_SZ];
static size_t out_pos = 0;

static inline void flush() {
    if (out_pos) {
        fwrite(outbuf, 1, out_pos, stdout);
        out_pos = 0;
    }
}

static inline void pt(char c) {
    if (out_pos + 1 >= OUT_BUF_SZ) flush();
    outbuf[out_pos++] = c;
}

static inline void pt(ll x) {
    if (out_pos + 80 >= OUT_BUF_SZ) flush();
    if (x == 0) {
        outbuf[out_pos++] = '0';
        outbuf[out_pos++] = '\n';
        return;
    }
    if (x < 0) {
        outbuf[out_pos++] = '-';
        x = -x;
    }
    char tmp[64];
    int tp = 0;
    while (x > 0) {
        tmp[tp++] = char('0' + (int)(x % 10));
        x /= 10;
    }
    for (int i = tp - 1; i >= 0; --i) outbuf[out_pos++] = tmp[i];
    outbuf[out_pos++] = '\n';
}

int main() {
    int t = (int)rd();
    while (t--) {
        ll l = rd();
        ll r = rd();
        ll k = rd();
        if (k < 2) k = 2;
        if (k > r - l + 1) { pt('0'); pt('\n'); continue; }
        ll limit = r / k;
        if (limit <= 0) { pt('0'); pt('\n'); continue; }

        ll lm = (l > 0 ? l - 1 : 0);
        ll ans = 0;

        for (ll g = 1; g <= limit; ) {
            ll u = r / g;
            ll v = (lm == 0 ? 0 : (lm / g));
            ll r1 = (u == 0 ? r : (r / u));
            ll r2 = (v == 0 ? limit : (lm / v));
            ll ng = r1 < r2 ? r1 : r2;
            if (ng > limit) ng = limit;
            if (ng < g) ng = g;

            ll cnt = u - v;
            if (cnt < k) {
                break;
            }
            ll cand = ng * ng;
            cand *= u + v;
            cand *= (cnt - 1);
            cand /= 2;
            if (cand > ans) ans = cand;

            g = ng + 1;
        }

        pt(ans);
    }
    flush();
    return 0;
}
