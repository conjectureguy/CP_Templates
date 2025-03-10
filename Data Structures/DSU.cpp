struct DSU {
  vector<int> par, rnk, sze;
  int c;
  DSU(int n) : par(n + 1), rnk(n + 1, 0), sze(n + 1, 1), c(n) {
    for (int i = 1; i <= n; ++i) par[i] = i;
  }
  int find(int i) {
    return (par[i] == i ? i : (par[i] = find(par[i])));
  }
  bool same(int i, int j) {
    return find(i) == find(j);
  }
  int get_size(int i) {
    return sze[find(i)];
  }
  int count() {
    return c;    //connected components
  }
  int merge(int i, int j) {
    if ((i = find(i)) == (j = find(j))) return -1;
    else --c;
    if (rnk[i] > rnk[j]) swap(i, j);
    par[i] = j;
    sze[j] += sze[i];
    if (rnk[i] == rnk[j]) rnk[j]++;
    return j;
  }
};
