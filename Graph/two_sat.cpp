struct two_sat {
  ll n;
  vector<vll> g, gr; // gr is the reversed graph
  vll comp, topological_order, answer; // comp[v]: ID of the SCC containing node v
  vector<bool> vis;

  two_sat() {}

  two_sat(ll _n) { init(_n); }

  void init(ll _n) {
    n = _n;
    g.assign(2 * n, vll());
    gr.assign(2 * n, vll());
    comp.resize(2 * n);
    vis.resize(2 * n);
    answer.resize(2 * n);
  }

  void add_edge(ll u, ll v) {
    g[u].push_back(v);
    gr[v].push_back(u);
  }

  // For the following three functions
  // int x, bool val: if 'val' is true, we take the variable to be x. Otherwise we take it to be x's complement.

  // At least one of them is true
  void add_clause_or(ll i, bool f, ll j, bool g) {
    add_edge(i + (f ? n : 0), j + (g ? 0 : n));
    add_edge(j + (g ? n : 0), i + (f ? 0 : n));
  }

  // Only one of them is true
  void add_clause_xor(ll i, bool f, ll j, bool g) {
    add_clause_or(i, f, j, g);
    add_clause_or(i, !f, j, !g);
  }

  // Both of them have the same value
  void add_clause_and(ll i, bool f, ll j, bool g) {
    add_clause_xor(i, !f, j, g);
  }

  // Topological sort
  void dfs(ll u) {
    vis[u] = true;

    for (const auto &v : g[u])
      if (!vis[v]) dfs(v);

    topological_order.push_back(u);
  }

  // Extracting strongly connected components
  void scc(ll u, ll id) {
    vis[u] = true;
    comp[u] = id;

    for (const auto &v : gr[u])
      if (!vis[v]) scc(v, id);
  }

  // Returns true if the given proposition is satisfiable and constructs a valid assignment
  bool satisfiable() {
    fill(vis.begin(), vis.end(), false);

    for (int i = 0; i < 2 * n; i++)
      if (!vis[i]) dfs(i);

    fill(vis.begin(), vis.end(), false);
    reverse(topological_order.begin(), topological_order.end());

    ll id = 0;
    for (const auto &v : topological_order)
      if (!vis[v]) scc(v, id++);

      // Constructing the answer
    for (int i = 0; i < n; i++) {
      if (comp[i] == comp[i + n]) return false;
      answer[i] = (comp[i] > comp[i + n] ? 1 : 0);
    }

    return true;
  }
};
