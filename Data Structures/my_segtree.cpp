struct node{
  ll val;
};

struct segtree{
  vll a;
  vector<node> seg;
  ll n;
  node identity_element;
  
  segtree(const vll& v){
    n = sz(v);
    seg = vector<node>(4*n);
    a = v;
    build(0, n-1, 1);
  }

  node combine(node x, node y){
    node nd;
    // implement
    return nd;
  }

  void build(ll l, ll r, ll id){
    if(l > r) return;
    if (l == r){
      seg[id].val = a[l];
      return;
    }
    ll mid = l + (r-l)/2;
    build(l, mid, 2*id);
    build(mid+1, r, 2*id + 1);
    seg[id] = combine(seg[2*id], seg[2*id+1]);
    return;
  }

  node query(ll id, ll tl, ll tr, ll l, ll r){
    if (tr < l || r < tl || tl > tr || l > r)
    {
      return identity_element;
    }
    if (l <= tl && tr <= r)
    {
      return seg[id];
    }
    ll mid = tl + (tr-tl)/2;
    node ans = combine(query(2*id, tl, mid, l, r), query(2*id+1, mid+1, tr, l, r));
    return ans;
  }

  void update(ll loc, ll x, ll id, ll tl, ll tr){
    if (loc < tl || loc > tr || tl > tr)
    {
      return;
    }
    if (loc == tl && tl == tr)
    {
      seg[id].val = x;
      return;
    }
    ll mid = tl + (tr-tl)/2;
    update(loc, x, 2*id, tl, mid);
    update(loc, x, 2*id+1, mid+1, tr);
    seg[id] = combine(seg[2*id], seg[2*id+1]);
    return;
  }

  node query(ll l, ll r){
    return query(1, 0, n-1, l, r);
  }

  void update(ll loc, ll x){
    update(loc, x, 1, 0, n-1);
  }
};
