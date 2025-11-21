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
constexpr int maxn = 1e4 + 10;
constexpr ll G = 3;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ull randint(ull l, ull r) {uniform_int_distribution<unsigned long long> dist(l, r); return dist(rng);}

template<class T>
constexpr T ksm(T a, ll b) {
	T res = 1;
	for (; b; b /= 2, a *= a) {
		if (b % 2) {
			res *= a;
		}
	}
	return res;
}

template<int P>
struct MInt {
	int x;
	constexpr MInt() : x{} {}
	constexpr MInt(long long v) : x{norm(v % getMod())} {}

	static int Mod;
	constexpr static int getMod() {
		if (P > 0) return P;
		else return Mod;
	}
	constexpr static void setMod(int Mod_) {
		Mod = Mod_;
	}
	constexpr static int norm(long long v) {
		if (v < 0) v += getMod();
		if (v >= getMod()) v -= getMod();
		return int(v);
	}

	constexpr int val() const { return x; }
	explicit constexpr operator int() const { return x; }

	constexpr MInt operator-() const {
		return MInt(norm(getMod() - x));
	}

	constexpr MInt inv() const {
		assert(x != 0);
		return pow(getMod() - 2);
	}

	constexpr MInt pow(long long e) const {
		MInt res(1), base(*this);
		while (e > 0) {
			if (e & 1) res *= base;
			base *= base;
			e >>= 1;
		}
		return res;
	}

	constexpr MInt &operator*=(MInt rhs) & {
		x = int(1LL * x * rhs.x % getMod());
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

	friend constexpr MInt operator*(MInt lhs, MInt rhs) { return lhs *= rhs; }
	friend constexpr MInt operator+(MInt lhs, MInt rhs) { return lhs += rhs; }
	friend constexpr MInt operator-(MInt lhs, MInt rhs) { return lhs -= rhs; }
	friend constexpr MInt operator/(MInt lhs, MInt rhs) { return lhs /= rhs; }

	friend istream &operator>>(std::istream &is, MInt &a) {
		long long v;
		is >> v;
		a = MInt(v);
		return is;
	}
	friend ostream &operator<<(std::ostream &os, const MInt &a) {
		return os << a.val();
	}

	friend constexpr bool operator==(MInt lhs, MInt rhs) { return lhs.val() == rhs.val(); }
	friend constexpr bool operator!=(MInt lhs, MInt rhs) { return lhs.val() != rhs.val(); }
};

template<>
int MInt<0>::Mod = 998244353;

typedef MInt<MOD> Z;


struct Comb {
	int n;
	vector<Z> _fac;
	vector<Z> _invfac;
	vector<Z> _inv;

	Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
	Comb(int n) : Comb() {
		init(n);
	}

	void init(int m) {
		if (m <= n) return;
		_fac.resize(m + 1);
		_invfac.resize(m + 1);
		_inv.resize(m + 1);

		for (int i = n + 1; i <= m; i++) {
			_fac[i] = _fac[i - 1] * i;
		}
		_invfac[m] = _fac[m].inv();
		for (int i = m; i > n; i--) {
			_invfac[i - 1] = _invfac[i] * i;
			_inv[i] = _invfac[i] * _fac[i - 1];
		}
		n = m;
	}

	Z fac(int m) {
		if (m > n) init(2 * m);
		return _fac[m];
	}
	Z invfac(int m) {
		if (m > n) init(2 * m);
		return _invfac[m];
	}
	Z inv(int m) {
		if (m > n) init(2 * m);
		return _inv[m];
	}
	Z P(int n, int m) {
		if (n < m || m < 0) return 0;
		return fac(n) * invfac(n - m);
	}
	Z C(int n, int m) {
		if (n < m || m < 0) return 0;
		return fac(n) * invfac(m) * invfac(n - m);
	}
} C;

template<class Z, int G>
struct PolyNTT {
	static void ntt(vector<Z>& a, bool invert) {
		int n = (int)a.size();
		vector<int> rev(n);
		for (int i = 0; i < n; i++) {
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
			if (i < rev[i]) swap(a[i], a[rev[i]]);
		}
		for (int len = 2; len <= n; len <<= 1) {
			Z wlen = Z(G).pow((Z::getMod() - 1) / len);
			if (invert) wlen = wlen.inv();
			for (int i = 0; i < n; i += len) {
				Z w = 1;
				for (int j = 0; j < (len >> 1); j++) {
					Z u = a[i + j];
					Z v = a[i + j + (len >> 1)] * w;
					a[i + j] = u + v;
					a[i + j + (len >> 1)] = u - v;
					w *= wlen;
				}
			}
		}
		if (invert) {
			Z inv_n = Z(n).inv();
			for (auto &x : a) x *= inv_n;
		}
	}

	static vector<Z> add(vector<Z> a, vector<Z> b) {
		int n = max(a.size(), b.size());
		a.resize(n); b.resize(n);
		for (int i = 0; i < n; i++) a[i] += b[i];
		return a;
	}
	static vector<Z> sub(vector<Z> a, vector<Z> b) {
		int n = max(a.size(), b.size());
		a.resize(n); b.resize(n);
		for (int i = 0; i < n; i++) a[i] -= b[i];
		return a;
	}

	static vector<Z> multiply(vector<Z> a, vector<Z> b) {
		if (a.empty() || b.empty()) return {};
		int need = (int)a.size() + (int)b.size() - 1;
		int n = 1; while (n < need) n <<= 1;
		a.resize(n); b.resize(n);
		ntt(a, false); ntt(b, false);
		for (int i = 0; i < n; i++) a[i] *= b[i];
		ntt(a, true);
		a.resize(need);
		return a;
	}

	static vector<Z> divide(const vector<Z>& a, const vector<Z>& b) {
		int n = (int)a.size(), m = (int)b.size();
		if (n < m) return {Z(0)};
		vector<Z> ra(a.rbegin(), a.rend());
		vector<Z> rb(b.rbegin(), b.rend());
		vector<Z> rb_inv;
		poly_inv(rb, rb_inv, n - m + 1);
		vector<Z> q = multiply(ra, rb_inv);
		q.resize(n - m + 1);
		reverse(q.begin(), q.end());
		return q;
	}

	static vector<Z> mod(const vector<Z>& a, const vector<Z>& b) {
		if (a.size() < b.size()) return a;
		vector<Z> q = divide(a, b);
		vector<Z> r = sub(a, multiply(q, b));
		if ((int)r.size() >= (int)b.size()) r.resize(b.size() - 1);
		while (!r.empty() && r.back() == Z(0)) r.pop_back();
		return r;
	}

	static vector<Z> derivative(const vector<Z>& a) {
		int n = a.size();
		if (n <= 1) return {};
		vector<Z> r(n - 1);
		for (int i = 1; i < n; i++) r[i - 1] = a[i] * Z(i);
		return r;
	}

	static vector<Z> integral(const vector<Z>& a) {
		int n = a.size();
		vector<Z> r(n + 1); r[0] = Z(0);
		for (int i = 0; i < n; i++) r[i + 1] = a[i] / Z(i + 1);
		return r;
	}

	static void poly_inv(const vector<Z>& a, vector<Z>& b, int deg) {
		if (deg == 1) { b.assign(1, a[0].inv()); return; }
		poly_inv(a, b, (deg + 1) >> 1);
		int n = 1; while (n < (deg << 1)) n <<= 1;
		vector<Z> f(a.begin(), a.begin() + min((int)a.size(), deg));
		f.resize(n); b.resize(n);
		ntt(f, false); ntt(b, false);
		for (int i = 0; i < n; i++) {
			b[i] = b[i] * (Z(2) - f[i] * b[i]);
		}
		ntt(b, true);
		b.resize(deg);
	}

	static void ln(const vector<Z>& a, vector<Z>& out, int deg) {
		vector<Z> der = derivative(a);
		vector<Z> inv;
		poly_inv(a, inv, deg);
		vector<Z> t = multiply(der, inv);
		if ((int)t.size() > deg - 1) t.resize(deg - 1);
		out = integral(t);
		out.resize(deg);
	}

	static void exp(const vector<Z>& a, vector<Z>& out, int deg) {
		if (deg == 1) { out.assign(1, Z(1)); return; }
		exp(a, out, (deg + 1) >> 1);
		out.resize(deg);
		vector<Z> ln_b;
		ln(out, ln_b, deg);
		vector<Z> s(a.begin(), a.begin() + min((int)a.size(), deg));
		for (int i = 0; i < deg; i++) ln_b[i] = s[i] - ln_b[i];
		ln_b[0] += Z(1);
		out = multiply(out, ln_b);
		out.resize(deg);
	}

	static void build_eval_tree(vector<vector<Z>>& tr, const vector<Z>& xs, int u, int l, int r) {
		if (r - l == 1) {
			tr[u] = { -xs[l], Z(1) };
		} else {
			int m = (l + r) >> 1;
			build_eval_tree(tr, xs, u << 1, l, m);
			build_eval_tree(tr, xs, u << 1 | 1, m, r);
			tr[u] = multiply(tr[u << 1], tr[u << 1 | 1]);
		}
	}

	static void fast_eval_rec(const vector<Z>& f, const vector<vector<Z>>& tr, vector<Z>& res, int u, int l, int r) {
		if (r - l == 1) {
			res[l] = f.empty() ? Z(0) : f[0];
			return;
		}
		vector<Z> rem = mod(f, tr[u]);
		int m = (l + r) >> 1;
		fast_eval_rec(rem, tr, res, u << 1, l, m);
		fast_eval_rec(rem, tr, res, u << 1 | 1, m, r);
	}

	static vector<Z> fast_eval(const vector<Z>& f, const vector<Z>& xs) {
		int n = xs.size();
		vector<vector<Z>> tr(n * 4);
		build_eval_tree(tr, xs, 1, 0, n);
		vector<Z> res(n);
		fast_eval_rec(f, tr, res, 1, 0, n);
		return res;
	}

	static vector<Z> interpolate(const vector<Z>& xs, const vector<Z>& ys) {
		int n = xs.size();
		vector<vector<Z>> tr(n * 4);
		build_eval_tree(tr, xs, 1, 0, n);
		vector<Z> all = tr[1];
		vector<Z> der = derivative(all);
		vector<Z> val = fast_eval(der, xs);
		vector<Z> w(n);
		for (int i = 0; i < n; i++) w[i] = ys[i] / val[i];

		function<vector<Z>(int, int, int)> dfs = [&](int u, int l, int r) -> vector<Z> {
			if (r - l == 1) return vector<Z>{ w[l] };
			int m = (l + r) >> 1;
			vector<Z> L = dfs(u << 1, l, m);
			vector<Z> R = dfs(u << 1 | 1, m, r);
			return add( multiply(L, tr[u << 1 | 1]), multiply(R, tr[u << 1]) );
		};
		return dfs(1, 0, n);
	}
};

using NTT = PolyNTT<Z, G>;

vector<Z> B(maxn);
vector<int> spf(maxn), primes, mu(maxn);

void init() {
	vector<Z> S(maxn, 0);
	for (int i = 0; i < maxn; ++i) {
		S[i] = C.invfac(i + 1);
	}
	vector<Z> A;
	NTT::poly_inv(S, A, maxn);
	for (int i = 0; i < maxn; ++i) B[i] = A[i] * C.fac(i);
}

vector<Z> calc(int p, ll K, const vector<Z>& B) {
	int need = p + 3;
	vector<Z> b(need);
	for (int j = 0; j < need; ++j) b[j] = B[j] * C.invfac(j);
	vector<Z> k(need);
	k[0] = Z(1);
	Z zK = Z(K % MOD);
	for (int t = 1; t < need; ++t) k[t] = k[t - 1] * zK;
	for (int t = 0; t < need; ++t) k[t] *= C.invfac(t);
	vector<Z> c = NTT::multiply(b, k);
	vector<Z> Pr(p + 2);
	for (int r = 0; r <= p + 1; ++r) {
		int idx = r + 1;
		Z val = (idx < (int)c.size() ? c[idx] : Z(0));
		Z left = C.fac(r + 1) * val;
		Z numer = left - B[r + 1];
		Pr[r] = numer / Z(r + 1);
	}
	return Pr;
}

void solve() {
	int n, d, p;
	cin >> n >> d >> p;
	if (n % d != 0) {
		cout << 0 << "\n";
		return;
	}
	int m = n / d;

	vector<int> frac; {
		int tmp = m;
		for (int i = 2; i * i <= tmp; ++i) {
			if (tmp % i == 0) frac.pb(i);
			while (tmp % i == 0) tmp /= i;
		}
		if (tmp > 1) frac.pb(tmp);
	}

	vector<Z> c(p + 2);
	int f = (p & 1) ? -1 : 1;
	for (int r = 1; r <= p + 1; ++r) {
		c[r] = f * C.C(p + 1, p + 1 - r) * B[p + 1 - r] / (p + 1);
		f = -f;
	}

	int k = frac.size();

	struct Node { ll s; ll K; int mu; };
	vector<Node> entries;
	for (int mask = 0; mask < (1 << k); ++mask) {
		ll s = 1; int bits = 0;
		for (int j = 0; j < k; ++j) {
			if (mask >> j & 1) { s *= frac[j]; ++bits; }
		}
		int mu = (bits % 2 == 0) ? 1 : -1;
		ll K = m / s;
		entries.pb({s, K, mu});
	}

	unordered_map<ll, vector<Z>> pr;
	for (auto &e : entries) {
		if (pr.find(e.K) == pr.end()) {
			pr[e.K] = calc(p, e.K, B);
		}
	}

	vector<Z> S(p + 2);
	for (auto &e : entries) {
		const vector<Z> &Pr = pr[e.K];
		Z spow = Z(1), zs = Z(e.s % MOD);
		for (int r = 0; r <= p + 1; ++r) {
			Z add = Pr[r] * spow;
			if (e.mu == 1) S[r] += add;
			else S[r] -= add;
			spow *= zs;
		}
	}

	Z ans(0), pd(d);
	for (int r = 1; r <= p + 1; ++r) {
		ans += c[r] * pd * S[r];
		pd *= d;
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