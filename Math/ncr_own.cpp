const int N = 5005;
ll fact[N], invfact[N];

ll binpow(ll a, ll b, ll m)
{
  a %= m;
  ll res = 1;
  while (b > 0)
  {
    if (b & 1)
    {
      res = res * a % m;
    }
    a = a * a % m;
    b >>= 1;
  }
  return res;
}

ll modInverse(ll n, ll p)
{
  return binpow(n, p - 2, p);
}

ll norma(ll x){
  x %= MOD;
  if (x < 0)
  {
    x += MOD;
  }
  return x;
}

ll mult(ll x, ll y){
  ll t = x*y;
  t = norma(t);
  return t;
}

ll add(ll x, ll y){
  ll t = x + y;
  t = norma(t);
  return t;
}

ll ncr(ll n, ll r){
  if (r < 0 || r > n) return 0;
  ll a1 = fact[n], a2 = invfact[r], a3 = invfact[n-r];
  ll ans = mult(a1, mult(a2, a3));
  return ans;
}

void factinit(){
  fact[0] = 1;
  for (ll i = 1; i < N; ++i)
  {
    fact[i] = mult(fact[i-1], i);
  }
  invfact[N-1] = modInverse(fact[N-1], MOD);
  for (ll i = N-2; i >= 0; --i)
  {
    invfact[i] = mult(invfact[i+1], i+1);
  }
}