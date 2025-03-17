template <int mod>
struct ModInt {
  int x;
 
  ModInt() : x(0) {}
 
  ModInt(int64_t y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}
 
  ModInt &operator+=(const ModInt &p) {
    if ((x += p.x) >= mod) x -= mod;
    return *this;
  }
 
  ModInt &operator-=(const ModInt &p) {
    if ((x += mod - p.x) >= mod) x -= mod;
    return *this;
  }
 
  ModInt &operator*=(const ModInt &p) {
    x = (int)(1LL * x * p.x % mod);
    return *this;
  }
 
  ModInt &operator/=(const ModInt &p) {
    *this *= p.inverse();
    return *this;
  }
 
  ModInt operator-() const { return ModInt(-x); }
  ModInt operator+() const { return ModInt(*this); }
 
  ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
 
  ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
 
  ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
 
  ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
 
  bool operator==(const ModInt &p) const { return x == p.x; }
 
  bool operator!=(const ModInt &p) const { return x != p.x; }
 
  ModInt inverse() const {
    int a = x, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b);
      swap(u -= t * v, v);
    }
    return ModInt(u);
  }
 
  ModInt pow(int64_t n) const {
    ModInt ret(1), mul(x);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
 
  friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.x; }
 
  friend istream &operator>>(istream &is, ModInt &a) {
    int64_t t;
    is >> t;
    a = ModInt<mod>(t);
    return (is);
  }
 
  int get() const { return x; }
 
  static constexpr int get_mod() { return mod; }
};
 
/**
 * @brief modint
 */
using mint = ModInt<MOD>;
 
const int N = 1 << 20;
vector<mint> fact(N), invfact(N);
bool facinit = false;
 
void fact_init(){
  facinit = true;
  fact[0] = 1;
  for (int i = 1; i < N; ++i)
  {
    fact[i] = fact[i-1]*mint(i);
  }
  invfact[N-1] = fact[N-1].pow(MOD-2);
  for (int i = N-2; i >= 0; --i)
  {
    invfact[i] = invfact[i+1]*mint(i+1);
  }
}
 
mint C(ll n, ll r){
  if (!facinit)
  {
    fact_init();
  }
  if (r < 0 || r > n)
  {
    return mint(0);
  }
  return fact[n]*invfact[r]*invfact[n-r];
}
 
mint P(ll n, ll r){
  if (!facinit)
  {
    fact_init();
  }
  if (r < 0 || r > n)
  {
    return mint(0);
  }
  return fact[n]*invfact[n-r];
}
 
mint Solutions(ll n, ll r){
  //solutions to x1 + ... + xn = r 
  //xi >= 0
  return C(n + r - 1, n - 1);
}
 
 
const int mod = 998244353;
const int root = 3;
int lim, rev[N], w[N], wn[N], inv_lim;
int POW(int x, int y, int ans = 1) {
  for (; y; y >>= 1, x = (long long) x * x % mod) if (y & 1) ans = (long long) ans * x % mod;
  return ans;
}
void precompute(int len) {
  lim = wn[0] = 1; int s = -1;
  while (lim < len) lim <<= 1, ++s;
  for (int i = 0; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
  const int g = POW(root, (mod - 1) / lim);
  inv_lim = POW(lim, mod - 2);
  for (int i = 1; i < lim; ++i) wn[i] = (long long) wn[i - 1] * g % mod;
}
void ntt(vector<mint> &a, int typ) {
  for (int i = 0; i < lim; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int i = 1; i < lim; i <<= 1) {
    for (int j = 0, t = lim / i / 2; j < i; ++j) w[j] = wn[j * t];
    for (int j = 0; j < lim; j += i << 1) {
      for (int k = 0; k < i; ++k) {
        const mint x = a[k + j], y = a[k + j + i]*w[k];
        a[k + j] += y;
        a[k + j + i] = x - y;
      }
    }
  }
  if (!typ) {
    reverse(a.begin() + 1, a.begin() + lim);
    for (int i = 0; i < lim; ++i) a[i] *= inv_lim;
  }
}
vector<mint> multiply(vector<mint> &f, vector<mint> &g) {
  if (f.empty() or g.empty()) return {};
  int n = (int)f.size() + (int)g.size() - 1;
  if (n == 1) return {f[0]*g[0]};
  precompute(n);
  vector<mint> a = f, b = g;
  a.resize(lim); b.resize(lim);
  ntt(a, 1), ntt(b, 1);
  for (int i = 0; i < lim; ++i) a[i] *= b[i];
  ntt(a, 0);
  a.resize(n + 1);
  return a;
}
 
void __print(mint x){
  cerr << x;
}