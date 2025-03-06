struct node{
  ll mn, idx;
  node(): mn(INF), idx(-1){}
};

struct sparsetable{
  ll n;
  vll v;
  vector<vector<node>> mat;

  sparsetable(const vll &a){
    n = sz(a);
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0].resize(n);
    for (int i = 0; i < n; ++i)
    {
      mat[0][i].mn = a[i]; mat[0][i].idx = i;
    }
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = combine(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  node combine(node x, node y){
    node nd;
    if (x.mn <= y.mn)
    {
      nd.mn = x.mn;
      nd.idx = x.idx;
    }
    else if (x.mn > y.mn)
    {
      nd.mn = y.mn;
      nd.idx = y.idx;
    }
    return nd;
  }

  node query(ll from, ll to){
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return combine(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};
