//Another
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(),a.rend();
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef __int128 lll;
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
	constexpr MInt(ll v) : x{norm(v % getMod())} {}

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
	constexpr int norm(int v) const {
		if (v < 0) {
			v += getMod();
		}
		if (v >= getMod()) {
			v -= getMod();
		}
		return v;
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
		return ksm(*this, getMod() - 2);
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
	friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
		ll v;
		is >> v;
		a = MInt(v);
		return is;
	}
	friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
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
int MInt<0>::Mod = MOD;

using Z = MInt<MOD>;

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
	Z C(int n, int m) {
		if (n < m || m < 0) return 0;
		return fac(n) * invfac(m) * invfac(n - m);
	}
} C;


// LÓGICA DO PROBLEMA
const int MAXN = 100;
map<pair<int, int>, Z> dp[MAXN + 5][MAXN + 5];
bool visited[MAXN + 5][MAXN + 5];
int s[MAXN + 5];
int n;

const map<pair<int, int>, Z>& solve(int l, int r) {
	if (l + 1 >= r) {
		if (!visited[l][r]) {
			dp[l][r][ {0, 0}] = 1;
			visited[l][r] = true;
		}
		return dp[l][r];
	}
	if (visited[l][r]) {
		return dp[l][r];
	}

	map<pair<int, int>, Z> res;

	for (int p = l + 1; p < r; ++p) {
		const auto& L = solve(l, p);
		const auto& R = solve(p, r);
		Z comb = C.C(r - l - 2, p - l - 1);

		for (auto const& [sl, wl] : L) {
			int klL = sl.first;
			int kpL = sl.second;

			for (auto const& [sr, wr] : R) {
				int kpR = sr.first;
				int krR = sr.second;

				int sp = kpL + kpR;
				if (s[p] != -1 && s[p] != sp) {
					continue;
				}

				int lp = 0, rp = 0;
				if (!(l == 0 && r == n + 1)) {
					if (l == 0) rp = 1;
					else if (r == n + 1) lp = 1;
					else if (p - l <= r - p) lp = 1;
					else rp = 1;
				}

				int fkl = klL + lp;
				int fkr = krR + rp;

				Z term = wl * wr * comb;

				res[ {fkl, fkr}] += term;
			}
		}
	}

	visited[l][r] = true;
	return dp[l][r] = res;
}

void solve_case() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
	}

	for (int i = 0; i <= n + 1; ++i) {
		for (int j = 0; j <= n + 1; ++j) {
			dp[i][j].clear();
			visited[i][j] = false;
		}
	}

	const auto& res_map = solve(0, n + 1);
	Z ans = 0;
	for (auto const& [scores, ways] : res_map) {
		ans += ways;
	}
	cout << ans << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) {
		solve_case();
	}
	return 0;
}