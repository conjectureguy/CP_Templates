vll kmp(string s){
  ll n = sz(s);
  vll pi(n);
  for (int i = 1; i < n; ++i)
  {
    ll j = pi[i-1];
    while(j > 0 && s[i] != s[j]) j = pi[j-1];
    if(s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}
