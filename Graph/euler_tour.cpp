ll n;
vector<vll> adj;
vll tin, tout;
ll t = 0;
vll tour;

void dfs(ll u, ll p){
  tin[u] = t++;
  for(auto it: adj[u]){
    if (it != p)
    {
      dfs(it, u);
    }
  }
  tout[u] = t-1;
}
