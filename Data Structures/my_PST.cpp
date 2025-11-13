struct Node{
  ll val;
  Node *l, *r;
  Node(ll x = 0): val(x), l(nullptr), r(nullptr){}
  Node(Node *cp) : val(cp->val), l(cp->l), r(cp->r) {}
  Node(Node *ll, Node *rr): val(ll->val + rr->val), l(ll), r(rr) {} 
};

struct PST{
  ll n;
  vll a;
  PST(const vll &A){
    a = A;
    n = sz(A);
  }

  Node* build(ll l, ll r){
    if (l == r) return new Node(a[l]);
    ll mid = l + (r-l)/2;
    return new Node(build(l, mid), build(mid+1, r));
  }

  ll query(Node *node, ll ql, ll qr, ll l, ll r){
    if (qr < l || r < ql || !node) return 0;
    if (ql <= l && r <= qr) return node->val;
    ll mid = l + (r-l)/2;
    return query(node->l, ql, qr, l, mid) + query(node->r, ql, qr, mid + 1, r);
  }

  Node* update(Node *node, ll x, ll loc, ll l, ll r){
    if (l == r) return new Node(x);
    ll mid = l + (r-l)/2;
    if (loc <= mid) return new Node(update(node->l, x, loc, l, mid), node->r);
    else return new Node(node->l, update(node->r, x, loc, mid + 1, r));
  }

  Node* build(){
    return build(0, n-1);
  }
  
  ll query(Node *node, ll ql, ll qr){
    return query(node, ql, qr, 0, n-1);
  }

  Node* update(Node* node, ll x, ll loc){
    return update(node, x, loc, 0, n-1);
  }

  void destroy(Node *node){
    if (!node) return;
    destroy(node->l);
    destroy(node->r);
    if (node) delete node;
  }
};