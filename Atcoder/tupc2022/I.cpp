//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef __int128 i128;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef tuple<ll, ll, ll> TLLL;
typedef __gnu_pbds::tree<PLL, __gnu_pbds::null_type, less<PLL>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;
// typedef __gnu_pbds::tree<ll, __gnu_pbds::null_type, less<ll>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> Tree;

constexpr int inf = (ll)1e9 + 7;
constexpr ll INF = (ll)2e18 + 9;
// constexpr ll INF = (ll)4e18;
// constexpr ll MOD = 1e9 + 7;
constexpr ll MOD = 998244353;
constexpr ld PI = acos(-1.0);
constexpr ld eps = 1e-10;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

template<class T>
constexpr T ksm(T a, ll b) {
	T res = 1;
	while (b) {
		if (b & 1) res *= a;
		b >>= 1;
		a *= a;
	}
	return res;
}

template<int P>
struct MInt {
	int x;
	constexpr MInt(): x() {}
	constexpr MInt(ll x) : x{norm(x % getMod())} {}
	static int Mod;
	constexpr static int getMod() {
		if (P > 0) {
			return P;
		} else {
			return Mod;
		}
	}
	constexpr static void setMod(int Mod_) {
		Mod = Mod_;
	}
	constexpr int norm(int x) const {
		if (x < 0) {
			x += getMod();
		}
		if (x >= getMod()) {
			x -= getMod();
		}
		return x;
	}
	constexpr int val() const {
		return x;
	}
	explicit constexpr operator int() const {
		return x;
	}
	constexpr MInt operator-() const {
		MInt res;
		res.x = norm(getMod() - x);
		return res;
	}
	constexpr MInt inv() const {
		assert(x != 0);
		return power(*this, getMod() - 2);
	}
	constexpr MInt &operator*=(MInt rhs) & {
		x = 1LL * x * rhs.x % getMod();
		return *this;
	}
	constexpr MInt &operator+=(MInt rhs) & {
		x = norm(x + rhs.x);
		return *this;
	}
	constexpr MInt &operator-=(MInt rhs) & {
		x = norm(x - rhs.x);
		return *this;
	}
	constexpr MInt &operator/=(MInt rhs) & {
		return *this *= rhs.inv();
	}
	friend constexpr MInt operator*(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res *= rhs;
		return res;
	}
	friend constexpr MInt operator+(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res += rhs;
		return res;
	}
	friend constexpr MInt operator-(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res -= rhs;
		return res;
	}
	friend constexpr MInt operator/(MInt lhs, MInt rhs) {
		MInt res = lhs;
		res /= rhs;
		return res;
	}
	friend constexpr istream &operator>>(istream &is, MInt &a) {
		ll v;
		is >> v;
		a = MInt(v);
		return is;
	}
	friend constexpr ostream &operator<<(ostream &os, const MInt &a) {
		return os << a.val();
	}
	friend constexpr bool operator==(MInt lhs, MInt rhs) {
		return lhs.val() == rhs.val();
	}
	friend constexpr bool operator!=(MInt lhs, MInt rhs) {
		return lhs.val() != rhs.val();
	}
};

template<>
int MInt<0>::Mod = 998244353;

using Z = MInt<MOD>;

constexpr int maxn = 1e7;

unordered_map<int, Z> fMu;

vector<int> spf(maxn + 1), primes, phi(maxn + 1), mu(maxn + 1);
vector<ll> sphi(maxn + 1);

void init() {
	phi[1] = 1, mu[1] = 1;
	primes.push_back(1);

	for (int i = 2; i <= maxn; i++) {
		if (spf[i] == 0) spf[i] = i, phi[i] = i - 1, mu[i] = -1, primes.push_back(i);

		for (int j = 1; primes[j]*i <= maxn; j++) {
			int m = primes[j] * i;
			spf[m] = primes[j];

			if (i % primes[j] == 0) {
				phi[m] = phi[i] * primes[j];
				break;
			}
			phi[m] = phi[i] * (primes[j] - 1);
			mu[m] = -mu[i];
		}
	}

	for (int i = 1; i <= maxn; i++) {
		sphi[i] = sphi[i - 1] + phi[i];
		mu[i] += mu[i - 1];
	}
}

Z sumMu(int n) {
	if (n <= maxn) {
		return mu[n];
	}
	if (fMu.count(n)) {
		return fMu[n];
	}
	if (n == 0) {
		return 0;
	}
	Z ans = 1;
	int l = 2, r;
	while (l <= n) {
		r = n / (n / l);
		ans -= (r - l + 1) * sumMu(n / l);
		l = r + 1;
	}
	return ans;
}

void solve() {
	int L, R;
	cin >> L >> R;
	L--;
	Z ans = 0;
	int l = 1, r;
	while (l <= R) {
		r = R / (R / l);
		if (l <= L) r = min(r, L / (L / l));
		ans += (ksm(Z(2), R / l - L / l) - 1) * (sumMu(r) - sumMu(l - 1));
		l = r + 1;
	}
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	init();

	int t = 1;
	// cin >> t;
	for (int _ = 1; _ <= t; ++_) {
		solve();
	}
	return 0;
}