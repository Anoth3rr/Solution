#include<stdio.h>

typedef long long ll;

ll qmul(ll a, ll b) {ll res = 0; while (b) {if (b & 1)res = (res + a); a = (a + a); b >>= 1;} return res;}
ll qpow(ll a, ll k) {if (k == 0) return 1; ll t = 1; while (k != 0) {if (k & 1)t = qmul(t, a); k >>= 1; a = qmul(a, a);} return t;}

int main() {
    ll x, y, z;
    scanf("%lld%lld", &x, &y);
    z = qpow(x, y);
    printf("%lld %lld\n", z, z % 1000);
    return 0;
}