ll bfs(ll s, ll t, vector<ll>& parent, vector<vll> &adj, vector<vll> &capacity) {
  fill(parent.begin(), parent.end(), -1);
  parent[s] = -2;
  queue<pair<ll, ll>> q;
  q.push({s, INF});

  while (!q.empty()) {
    ll cur = q.front().first;
    ll flow = q.front().second;
    q.pop();

    for (ll next : adj[cur]) {
      if (parent[next] == -1 && capacity[cur][next]) {
        parent[next] = cur;
        ll new_flow = min(flow, capacity[cur][next]);
        if (next == t)
          return new_flow;
        q.push({next, new_flow});
      }
    }
  }
  return 0;
}

ll maxflow(ll s, ll t, vector<vll> &adj, vector<vll> &capacity) {
  ll n = sz(adj);
  ll flow = 0;
  vector<ll> parent(n);
  ll new_flow;

  while (new_flow = bfs(s, t, parent, adj, capacity)) {
    flow += new_flow;
    ll cur = t;
    while (cur != s) {
      ll prev = parent[cur];
      capacity[prev][cur] -= new_flow;
      capacity[cur][prev] += new_flow;
      cur = prev;
    }
  }
  return flow;
}
