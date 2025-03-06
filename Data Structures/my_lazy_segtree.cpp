struct node{

};

struct segtree{
  vll a;
  vector<node> seg;
  ll n;
  node identity_element;
  
  segtree(const vll& v){
    n = static_cast<int>(sz(v));
    seg = vector<node>(4*n);
    a = v;
    build(0, n-1, 1);
  }

  node combine(node x, node y){
    node nd;
    // implement
    return nd;
  }

  void push(ll id, ll tl, ll tr){
    if(tl > tr) return;
    if (lazy)
    {
      
    }
  }

  void build(ll l, ll r, ll id){
    if(l > r) return;
    if (l == r){
      // implement
      return;
    }
    ll mid = l + (r-l)/2;
    build(l, mid, 2*id);
    build(mid+1, r, 2*id + 1);
    seg[id] = combine(seg[2*id], seg[2*id+1]);
    return;
  }

  node query(ll id, ll tl, ll tr, ll l, ll r){
    push(id, tl, tr);
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

  void update(ll l, ll r, ll x, ll id, ll tl, ll tr){
    push(id, tl, tr);
    if (tr < l || r < tl || tl > tr || l > r)
    {
      return;
    }
    if (l <= tl && tr <= r)
    {
      // implement
      push(id, tl, tr);
      return;
    }
    ll mid = tl + (tr-tl)/2;
    update(l, r, x, 2*id, tl, mid);
    update(l, r, x, 2*id+1, mid+1, tr);
    seg[id] = combine(seg[2*id], seg[2*id+1]);
    return;
  }

  node query(ll l, ll r){
    return query(1, 0, n-1, l, r);
  }

  void update(ll l, ll r, ll x){
    update(l, r, x, 1, 0, n-1);
  }
};
