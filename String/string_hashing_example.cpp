const ll P = 31;
const ll M = 2147483647;
const int N = 1000005;
vll p_pow(N);

ll binpow(ll a, ll b, ll MD)
{
  a %= MD;
  ll res = 1;
  while(b > 0)
  {
    if (b&1)
    {
      res *= a; res %= MD;
    }
    a *= a; a %= MD;
    b >>= 1;
  }
  return res;
}
#error add precomp to main
void precomp(){
  p_pow[0] = 1;
  for (int i = 1; i < N; ++i)
  {
    p_pow[i] = p_pow[i-1]*P;
    p_pow[i] %= M;
  }
}

ll mult(ll x, ll y, ll MD){
  ll t = x*y;
  t %= MD;
  if (t < 0)
  {
    t += MD;
  }
  return t;
}

ll add(ll x, ll y, ll MD){
  ll t = x+y;
  if (t >= MD)
  {
    t -= MD;
  }
  if (t < 0)
  {
    t += MD;
  }
  return t;
}

void solve(int ts = 1)
{
  string s; cin >> s;
  ll n = s.size();
  vll hash(n+1, 0);
  s = "1" + s;
  for (int i = 1; i <= n; ++i)
  {
    hash[i] = (hash[i-1] + (s[i]-'a'+1)*p_pow[i-1])%M;
  }
  ll cnt = 0;
  for (int i = 1; i < n; ++i)
  {
    ll pre = hash[i];
    ll suff = (hash[n] - hash[n-i] + M)%M;
    if (suff == (pre*p_pow[n-i])%M)
    {
      cout << i << gap;
    }
  }
  cout << endl;
}