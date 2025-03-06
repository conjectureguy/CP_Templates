ll get_lca(ll u, ll v){
  if(dep[u] < dep[v]) swap(u, v);
  for (int i = LG-1; i >= 0; --i)
  {
    if (dep[par[i][u]] >= dep[v]) u = par[i][u];
  }
  if(u == v) return u;
  for (int i = LG-1; i >= 0; --i)
  {
    if (par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
  }
  assert(u != v && par[0][u] == par[0][v]);
  return par[0][u];
}
