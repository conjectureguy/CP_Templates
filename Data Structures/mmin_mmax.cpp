auto mmax = [&](ll a, ll b){
    return max(a, b);
  };
  auto mmin = [&](ll a, ll b){
    return min(a, b);
  };
  SparseTable<ll, decltype(mmax)> st1(a, mmax);
  SparseTable<ll, decltype(mmin)> st2(b, mmin);
