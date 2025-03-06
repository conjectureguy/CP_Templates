vll z_function(string s){
  ll n = sz(s), l = 0, r = 0;
  vll z(n);
  for (int i = 0; i < n; ++i)
  {
    if(i < r) z[i] = min(r-i, z[i-l]);
    while(i + z[i] < n && s[z[i]] == s[i+z[i]]) z[i]++;
    if (i+z[i] > r)
    {
      l = i; r = i + z[i];
    }
  }
  return z;
}
