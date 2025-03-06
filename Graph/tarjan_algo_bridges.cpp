// https://cp-algorithms.com/graph/bridge-searching.html
ll n;
vector<vll> adj;
vpll isbridge;

void IS_BRIDGE(int v,int to){
  isbridge.pb({v, to});
}

vector<bool> visited;
vll tin, low, sizes;
ll timer;

void dfs(ll v, ll p = -1) {
  visited[v] = true;
  tin[v] = low[v] = timer++;
  sizes[v] = 1;
  bool parent_skipped = false;
  for(ll to : adj[v]){
    if(to == p && !parent_skipped) {
      parent_skipped = true;
      continue;
    }
    if(visited[to]) {
      low[v] = min(low[v], tin[to]);
    }
    else{
      dfs(to, v);
      low[v] = min(low[v], low[to]);
      if (low[to] > tin[v]){
        IS_BRIDGE(v, to);
      }
      sizes[v] += sizes[to];
    }
  }
}

void find_bridges() {
  timer = 0;
  visited.assign(n, false);
  sizes.assign(n, 0);
  tin.assign(n, -1);
  low.assign(n, -1);
  for (int i = 0; i < n; ++i) {
    if (!visited[i])
      dfs(i);
  }
}
