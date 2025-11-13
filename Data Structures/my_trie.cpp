struct Trie {
  static const int B = 31;
  struct node{
    array<ll,2> nxt;
    ll mxidx;
    node(){
      nxt[0] = nxt[1] = 0;
      mxidx = -1;
    }
  };
  vector<node> vTrie;
  Trie(){
    vTrie.resize(2);
  }
  void insert(ll val, ll idx){
    ll cur = 1;
    for (int i = B - 1; i >= 0; i--) {
      int b = val >> i & 1;
      if (vTrie[cur].nxt[b] == 0){
        vTrie[cur].nxt[b] = sz(vTrie);
        vTrie.push_back(node());
      }
      cur = vTrie[cur].nxt[b];
      vTrie[cur].mxidx = max(vTrie[cur].mxidx, idx);
    }
  }
  ll query(ll x, ll k) { 
    ll cur = 1;
    ll rightmost = -1;
    for (int i = B - 1; i >= 0; i--) {
      if (cur == 0) break;
      int b1 = x >> i & 1, b2 = k >> i & 1;
      if (b2 == 1) {
        if (vTrie[cur].nxt[b1]) rightmost = max(rightmost, vTrie[vTrie[cur].nxt[b1]].mxidx);
        cur = vTrie[cur].nxt[!b1];
      } else cur = vTrie[cur].nxt[b1];
    }
    return rightmost;
  }
  void clear(){
    for (int i = 0; i < sz(vTrie); ++i) vTrie[i].mxidx = -1;
  }
};