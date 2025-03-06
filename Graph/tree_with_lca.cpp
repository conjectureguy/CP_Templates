struct Tree{
  ll n, lg, root;
  vector<vll> adj, par;
  vll dep;

  Tree(ll _n){
    _n++; n = _n;
    lg = __lg(n) + 1;
    adj = vector<vll>(n);
    par = vector<vll>(lg, vll(n));
    dep.resize(n);
  }

  void add_edge(ll u, ll v){
    adj[u].pb(v); adj[v].pb(u);
  }

  void init(ll rt = 1){
    root = rt;
    dfs(root, 0);
  }

  void dfs(ll u, ll p){
    par[0][u] = p;
    dep[u] = dep[p] + 1;
    for (int i = 1; i < lg; ++i) par[i][u] = par[i-1][par[i-1][u]];
    for(auto it: adj[u]){
      if (it != p) dfs(it, u);
    }
  }

  ll lca(ll u, ll v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int k = lg-1; k >= 0; k--) if (dep[par[k][u]] >= dep[v]) u = par[k][u];
    if (u == v) return u;
    for (int k = lg-1; k >= 0; k--) if (par[k][u] != par[k][v]) u = par[k][u], v = par[k][v];
    return par[0][u];
  }

  ll kth(ll u, ll k) {
    assert(k >= 0);
    for (int i = 0; i < lg; i++) if (k & (1ll << i)) u = par[i][u];
    return u;
  }

  ll dist(ll u, ll v) {
    ll l = lca(u, v);
    return dep[u] + dep[v] - 2*dep[l];
  }

  //kth node from u to v, 0th node is u
  ll go(ll u, ll v, ll k) {
    ll l = lca(u, v);
    ll d = dist(u, v);
    assert(k <= d);
    if (dep[l] + k <= dep[u]) return kth(u, k);
    k -= dep[u] - dep[l];
    return kth(v, dep[v] - dep[l] - k);
  }
};
