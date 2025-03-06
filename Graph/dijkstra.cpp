vll dijk(vector<vpll> &adj){
  ll n = sz(adj);
  vll dist(n, INF);
  dist[0] = 0;
  pqg<pair<ll,ll>> pq;
  pq.push({0, 0});
  vector<bool> vis(n, false);
  while(sz(pq)){
    auto [d, node] = pq.top();
    pq.pop();
    if (vis[node]) continue;
    vis[node] = 1;
    for(auto [it, w]: adj[node]){
      if ((!vis[it]) && dist[node]+w < dist[it])
      {
        dist[it] = dist[node] + w;
        pq.push({dist[it], it});
      }
    }
  }
  return dist;
}
